#pragma once
#include <QtGui>

/**
 * @brief createModel 创建标准item model，用于table和view的视图项
 * @param parent
 * @param rows
 * @param cols
 * @param childNodes
 * @return
 */
QStandardItemModel* createModel(QObject *parent, int rows = 10,
                               int cols = 5, int childNodes = 5)
{
    QStandardItemModel *model = new QStandardItemModel(rows, cols, parent);
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            QStandardItem *item = new QStandardItem(QString("Row:%0, Column:%1")
                                                        .arg(c).arg(c));
            if (c == 0) {
                for (int i = 0; i < childNodes; i++) {
                    QStandardItem *child = new QStandardItem(QString("Item %0").arg(i));
                    item->appendRow(child);
                }
            }
            model->setItem(r, c, item);
        }
    }
    model->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Value"));
    return model;
}
