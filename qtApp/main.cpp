#include "TestQxOrm_all_include.model_view.gen.h"
#include "appController.h"
#include "projectListModel.h"
#include <QDebug>
#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>


using namespace FluoUI::DataBase;
using namespace FluoUI::DataBase::viewModel;

void insertDummyData() {
  auto john = QSharedPointer<FluoUI::DataBase::User>::create();
  john->setname("John Doe");
  qx::dao::insert(john);

  auto jane = QSharedPointer<FluoUI::DataBase::User>::create();
  jane->setname("Jane Smith");
  qx::dao::insert(jane);

  auto sam = QSharedPointer<FluoUI::DataBase::User>::create();
  sam->setname("Sam McFlury");
  qx::dao::insert(sam);

  Project_ptr p = std::make_shared<Project>();
  p->setname("Project Alpha");
  p->setcreationDate(QDateTime::currentDateTime());
  p->setuser(john);
  qx::dao::insert(p);

  p = std::make_shared<Project>();
  p->setname("Project Beta");
  p->setcreationDate(QDateTime::currentDateTime());
  p->setuser(jane);
  qx::dao::insert(p);

  p = std::make_shared<Project>();
  p->setname("Project Delta");
  p->setuser(sam);
  qx::dao::insert(p);

  p = std::make_shared<Project>();
  p->setcreationDate(QDateTime::currentDateTime());
  p->setname("Project Gamma");
  p->setuser(john);
  qx::dao::insert(p);
}

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  qx::QxSqlDatabase::getSingleton()->setDriverName("QSQLITE");
  qx::QxSqlDatabase::getSingleton()->setHostName("localhost");
  qx::QxSqlDatabase::getSingleton()->setUserName("root");
  qx::QxSqlDatabase::getSingleton()->setPassword("");

  QString dbPath =
      QCoreApplication::applicationDirPath() + "/awesomeTest.db.sqlite";
  qx::QxSqlDatabase::getSingleton()->setDatabaseName(dbPath);
  if (!QFile::exists(dbPath)) {
    qDebug() << "DB not found - creating new one";
    qx::dao::create_table<User>();
    qx::dao::create_table<Project>();
    insertDummyData();
  }

  //=========== DUM DUM  ============
  qx::dao::delete_all<Project>();
  qx::dao::delete_all<User>();
  insertDummyData();
  //=================================

  AppController::instance(qApp);
  qmlRegisterSingletonInstance<AppController>("Fluo", 1, 0, "AppController",
                                              AppController::instance());

  QQmlApplicationEngine engine;
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  engine.loadFromModule("qtApp", "Main");

  return app.exec();
}
