#include "studentitemmodel.h"

StudentItemModel::StudentItemModel(QObject *parent)
    : QStandardItemModel(parent)
{

}

Qt::ItemFlags StudentItemModel::flags(const QModelIndex &index) const
{
    if (!disableColumns.isEmpty() && disableColumns.indexOf(index.column()) != -1) {
        return QStandardItemModel::flags(index) ^ Qt::ItemIsEditable;
    }
    return QStandardItemModel::flags(index);
}

void StudentItemModel::setDisableColumns(QList<int> indexs)
{
    disableColumns = indexs;
}
