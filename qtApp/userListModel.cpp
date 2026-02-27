#include "userListModel.h"

UserModel::UserModel(QObject* parent) : QAbstractListModel(parent) {
	refresh();
}

int UserModel::rowCount(const QModelIndex&) const {
	return m_users.size();
}

QVariant UserModel::data(const QModelIndex& index, int role) const {
	if (!index.isValid())
		return QVariant();

	auto user = m_users[index.row()];

	if (role == NameRole) {
		return user->getname();
	}
	return QVariant();
}

QHash<int, QByteArray> UserModel::roleNames() const {
	return { {NameRole, "name"} };
}

void UserModel::refresh() {
	beginResetModel();

	m_users.clear();

	list_of_User users;
	qx::dao::fetch_all(users);

	for (auto it : users)
		m_users.append(it.second);

	endResetModel();
}