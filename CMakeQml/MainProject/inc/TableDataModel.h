#pragma once

#ifndef TABLEDATAMODEL_H
#define TABLEDATAMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <QStringList>

class TableDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableDataModel(QObject* parent = nullptr);

    // 定义表格列的枚举
    enum TableColumns {
        NameColumn = 0,
        SexColumn,
        IdColumn,
        OptionColumn,
        ColumnCount
    };

    // QAbstractItemModel 必须实现的接口
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // 添加数据行
    Q_INVOKABLE void appendRow(const QString& name, const QString& sex, const QString& id, bool option);

    // 删除数据行
    Q_INVOKABLE void deleteRow(int row);

private:
    struct TableEntry {
        QString name;
        QString sex;
        QString id;
        bool option;
    };

    QList<TableEntry> m_data;
};

#endif // TABLEDATAMODEL_H
