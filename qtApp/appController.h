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


		friend class QSingleton<AppController>;
	explicit AppController(QObject* parent = nullptr);
	virtual ~AppController();

public:

	Q_INVOKABLE void insertProject(const QString& name);
	qx::QxModel<Project>* getProject();
	Q_INVOKABLE void insertUser(const QString& name);
	qx::QxModel<User>* getUser();


signals:
	void projectChanged();
	void userChanged();
private:
	qx::QxModel<User>* _userModel;
	qx::QxModel<Project>* _projectModel;

};