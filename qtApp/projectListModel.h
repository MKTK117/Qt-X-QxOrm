#pragma once
#include "TestQxOrm_all_include.model_view.gen.h"
#include <QAbstractListModel>


using namespace FluoUI::DataBase;

class ProjectModel : public QAbstractListModel {
  Q_OBJECT

public:
  enum Roles { NameRole = Qt::UserRole + 1, UserRole };

  explicit ProjectModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;

  Q_INVOKABLE void refresh();

private:
  QList<Project_ptr> m_projects;
};