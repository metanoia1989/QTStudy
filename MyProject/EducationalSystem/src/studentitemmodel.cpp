#include "studentitemmodel.h"
#include <QMessageBox>
#include <QDebug>

StudentItemModel::StudentItemModel(QObject *parent)
    : QStandardItemModel(parent)
{
    msgBox = new QMessageBox(nullptr);
    msgBox->setIcon(QMessageBox::Information);
    msgBox->setWindowTitle("确认提示");
    msgBox->setText("确认要设置为已收齐吗？");
    msgBox->addButton("确认", QMessageBox::AcceptRole);
    msgBox->addButton("取消", QMessageBox::RejectRole);
}

StudentItemModel::~StudentItemModel()
{
    delete msgBox;
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

void StudentItemModel::setMaterialColumns(QList<int> indexs)
{
    materialColumns = indexs;
}

void StudentItemModel::setMaterialCompleteColumn(int column)
{
    materialCompleteColumn = column;
}

QList<int> StudentItemModel::getMaterialColumns()
{
    return materialColumns;
}

bool StudentItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
     if (index.isValid() && role == Qt::EditRole) {
        auto item = itemFromIndex(index);

        QList<QString> completeStatus = { "已收齐", "提前提交" }; // 资料收齐状态
        QString valueStr = value.toString();
        qDebug() << "数据为:" << valueStr;
        if (materialColumns.indexOf(index.column()) != -1 && completeStatus.indexOf(valueStr) != -1) {
            // 检测是否最后一个资料字段，是则进行提示
            int completeCount = 0;
            for(int i = 0; i<materialColumns.count(); i++) {
                int column = materialColumns.at(i);
                if (column == index.column()) continue;
                auto tI = this->index(index.row(), column);
                auto tItem = itemFromIndex(tI);
                QString tValue = tItem->data(Qt::EditRole).toString();
                if (completeStatus.indexOf(tValue) != -1) {
                    completeCount++;
                }
            }
            if (completeCount == materialColumns.count() - 1 && completeCount != 0) {
                int result = msgBox->exec();
                if (result == QMessageBox::AcceptRole) {
                    item->setData(value, Qt::EditRole);
                    auto materialItem = itemFromIndex(this->index(index.row(), materialCompleteColumn));
                    materialItem->setData("已收齐", Qt::DisplayRole);
                    materialItem->setData(QIcon(":/icons/tick.png"), Qt::DecorationRole);
                }
                return false;
            }
        }

        item->setData(value, Qt::EditRole);
        return true;
     }

     return QStandardItemModel::setData(index, value, role);
}
