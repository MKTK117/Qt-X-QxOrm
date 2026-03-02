#include "AppController.h"
#include "TestQxOrm_all_include.model_view.gen.h"
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


using namespace FluoUI::DataBase;
using namespace FluoUI::DataBase::viewModel;

AppController::AppController(QObject* parent) : QObject(parent) {
	_userModel = new qx::QxModel<User>(this);
	_projectModel = new qx::QxModel<Project>(this);
	_activeUserProjectsModel = new qx::QxModel<Project>(this);

	_userModel->qxFetchAll();
	_projectModel->qxFetchAll();
}
AppController::~AppController() {}

void AppController::insertProject(const QString& name) {
	Project_ptr project;

	project.reset(new Project());
	project->setname(name);
	project->setcreationDate(QDateTime::currentDateTime());
	qx::dao::insert(project);
	emit projectChanged();
}

qx::QxModel<Project>* AppController::getProject() {
	return _projectModel;
}

void AppController::insertUser(const QString& name) {
	User_ptr user;
	user.reset(new User());
	user->setname(name);
	qx::dao::insert(user);
	emit userChanged();
}

qx::QxModel<User>* AppController::getUser() {
	return _userModel;
}

void AppController::refreshAll() {
	_userModel->qxFetchAll();
	_projectModel->qxFetchAll();
}

void AppController::setActiveUser(long userId)
{
	_activeUserId = userId;

	qx::QxSqlQuery query;
	query.query("WHERE t_Project.user = :id");
	query.bind(":id", QVariant::fromValue(userId));

	_activeUserProjectsModel->qxFetchByQuery(query);

	emit projectChanged();
}

qx::QxModel<Project>* AppController::activeProjects()
{
	return _activeUserProjectsModel;
}