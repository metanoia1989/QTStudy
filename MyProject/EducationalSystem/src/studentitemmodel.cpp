#include "studentitemmodel.h"

StudentItemModel::StudentItemModel(QObject *parent)
    : QStandardItemModel(parent)
{

}

Qt::ItemFlags StudentItemModel::flags(const QModelIndex &index) const
{
    if (!disableColumns.isEmpty() && disableColumns.indexOf(index.column()) != -1) {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable ;
}

void StudentItemModel::setDisableColumns(QList<int> indexs)
{
    disableColumns = indexs;
}
