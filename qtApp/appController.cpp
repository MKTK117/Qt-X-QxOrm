#include "AppController.h"
#include "TestQxOrm_all_include.model_view.gen.h"
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


using namespace FluoUI::DataBase;
using namespace FluoUI::DataBase::viewModel;

AppController::AppController(QObject *parent) : QObject(parent) {}
AppController::~AppController() {}

void AppController::insertProject(const QString &name) {
  Project_ptr project;

  project.reset(new Project());
  project->setname(name);
  project->setcreationDate(QDateTime::currentDateTime());
  qx::dao::insert(project);
  emit projectChanged();
}

qx::QxModel<Project> *AppController::getProject() {
  auto *modelProject = new qx::QxModel<Project>();
  modelProject->qxFetchAll();
  return modelProject;
}

void AppController::insertUser(const QString &name) {
  User_ptr user;
  user.reset(new User());
  user->setname(name);
  qx::dao::insert(user);
  emit userChanged();
}

qx::QxModel<User> *AppController::getUser() {
  auto *modelUser = new qx::QxModel<User>();
  modelUser->qxFetchAll();
  return modelUser;
}
