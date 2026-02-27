#pragma once
#include "TestQxOrm_all_include.model_view.gen.h"
#include <QAbstractListModel>


using namespace FluoUI::DataBase;
using namespace FluoUI::DataBase::viewModel;


class UserModel : public QAbstractListModel {
	Q_OBJECT

public:
	enum Roles { NameRole = Qt::UserRole + 1 };

	explicit UserModel(QObject* parent = nullptr);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role) const override;
	QHash<int, QByteArray> roleNames() const override;

	Q_INVOKABLE void refresh();

private:
	QList<User_ptr> m_users;

};