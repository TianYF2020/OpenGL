#include "tabledatamodel.h"

TableDataModel::TableDataModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

int TableDataModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

int TableDataModel::columnCount(const QModelIndex& parent) const
{

    // 返回行值
    Q_UNUSED(parent);
    return ColumnCount;  // 返回总列数
}

QVariant TableDataModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    const TableEntry& entry = m_data[index.row()];

    switch (index.column()) {
    case NameColumn:
        return entry.name;
    case SexColumn:
        return entry.sex;
    case IdColumn:
        return entry.id;
    case OptionColumn:
        return entry.option ? "Yes" : "No";
    default:
        return QVariant();
    }
}

void TableDataModel::appendRow(const QString& name, const QString& sex, const QString& id, bool option)
{
    beginInsertRows(QModelIndex(), m_data.count(), m_data.count());
    m_data.append({ name, sex, id, option });
    endInsertRows();
}

void TableDataModel::deleteRow(int row)
{
    if (row >= 0 && row < m_data.count()) {
        beginRemoveRows(QModelIndex(), row, row);
        m_data.removeAt(row);
        endRemoveRows();
    }
}
