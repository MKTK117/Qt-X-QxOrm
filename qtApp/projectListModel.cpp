#include "projectListModel.h"

ProjectModel::ProjectModel(QObject *parent) : QAbstractListModel(parent) {
  refresh();
}

int ProjectModel::rowCount(const QModelIndex &) const {
  return m_projects.size();
}

QVariant ProjectModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  auto project = m_projects[index.row()];

  if (role == NameRole)
    return project->getname();
  else if (role == UserRole)
    return project->getuser() ? project->getuser()->getname() : "";

  return QVariant();
}

QHash<int, QByteArray> ProjectModel::roleNames() const {
  return {{NameRole, "name"}, {UserRole, "user"}};
}

void ProjectModel::refresh() {
  beginResetModel();

  m_projects.clear();

  list_of_Project projects;
  qx::dao::fetch_all(projects);

  for (auto it : projects)
    m_projects.append(it.second);

  endResetModel();
}