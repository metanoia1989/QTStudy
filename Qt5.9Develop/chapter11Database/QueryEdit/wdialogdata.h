#ifndef WDIALOGDATA_H
#define WDIALOGDATA_H

#include <QDialog>
#include <QSqlRecord>

namespace Ui {
class WDialogData;
}

class WDialogData : public QDialog
{
    Q_OBJECT

public:
    explicit WDialogData(QWidget *parent = nullptr);
    ~WDialogData();
    void setUpdateRecord(QSqlRecord &recData); // 更新记录
    void setInsertRecord(QSqlRecord &recData); // 插入记录
    QSqlRecord getRecordData(); // 获取录入的数据

private slots:
    void on_btnSetPhoto_clicked();

    void on_btnClearPhoto_clicked();

private:
    Ui::WDialogData *ui;
    QSqlRecord mRecord; // 保存一条记录的数据
};

#endif // WDIALOGDATA_H
