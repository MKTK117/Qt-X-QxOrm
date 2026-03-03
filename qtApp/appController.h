#pragma once
#include <QObject>
#include "TestQxOrm_all_include.model_view.gen.h"
#include "projectListModel.h"
#include "userListModel.h"
#include "QSingleton.h"
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
using namespace FluoUI::DataBase;
using namespace FluoUI::DataBase::viewModel;

class AppController : public QObject, public QSingleton<AppController> {
	Q_OBJECT

		Q_PROPERTY(qx::QxModel<Project>* project READ getProject NOTIFY projectChanged)
		Q_PROPERTY(qx::QxModel<User>* user READ getUser NOTIFY userChanged)
		Q_PROPERTY(qx::QxModel<Project>* activeProjects READ activeProjects NOTIFY projectChanged)


		friend class QSingleton<AppController>;
	explicit AppController(QObject* parent = nullptr);
	virtual ~AppController();

public:

	Q_INVOKABLE void insertProject(const QString& name, long userId);
	qx::QxModel<Project>* getProject();
	Q_INVOKABLE void insertUser(const QString& name);
	qx::QxModel<User>* getUser();
	Q_INVOKABLE void refreshAll();
	Q_INVOKABLE void setActiveUser(long id);
	qx::QxModel<Project>* activeProjects();
	Q_INVOKABLE void deleteUser(long userId);


signals:
	void projectChanged();
	void userChanged();
private:
	qx::QxModel<User>* _userModel;
	qx::QxModel<Project>* _projectModel;
	User_ptr _activeUser;
	long _activeUserId = -1;
	qx::QxModel<Project>* _activeUserProjectsModel = nullptr;

};