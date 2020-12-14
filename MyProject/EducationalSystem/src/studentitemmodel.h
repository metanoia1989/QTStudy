#ifndef STUDENTITEMMODEL_H
#define STUDENTITEMMODEL_H

#include <QStandardItemModel>

class QMessageBox;

class StudentItemModel : public QStandardItemModel
{
    Q_OBJECT
public:
    StudentItemModel(QObject *parent = nullptr);
    ~StudentItemModel();

    Qt::ItemFlags flags(const QModelIndex &index) const;

    void setDisableColumns(QList<int> indexs);
    void setMaterialColumns(QList<int> indexs);
    void setMaterialCompleteColumn(int column);
    QList<int> getMaterialColumns();


protected:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

private:
    QList<int> disableColumns;
    QList<int> materialColumns;
    int materialCompleteColumn; // 资料收齐字段
    QMessageBox *msgBox;

};

#endif // STUDENTITEMMODEL_H
