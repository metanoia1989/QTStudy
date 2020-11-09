#ifndef STUDENTITEMMODEL_H
#define STUDENTITEMMODEL_H

#include <QStandardItemModel>

class StudentItemModel : public QStandardItemModel
{
    Q_OBJECT
public:
    StudentItemModel(QObject *parent = nullptr);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    void setDisableColumns(QList<int> indexs);

private:
    QList<int> disableColumns;
};

#endif // STUDENTITEMMODEL_H
