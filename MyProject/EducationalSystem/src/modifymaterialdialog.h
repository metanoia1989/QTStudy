#ifndef MODIFYMATERIALDIALOG_H
#define MODIFYMATERIALDIALOG_H

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class ModifyMaterialDialog;
}

class ModifyMaterialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyMaterialDialog(QWidget *parent = nullptr);
    ~ModifyMaterialDialog();

    QMap<QString, int> getResults();

    void clearChecked();

private:
    Ui::ModifyMaterialDialog *ui;

    QButtonGroup *techGroup; // 教材是否寄出
    QButtonGroup *paperGroup; // 纸质版照片
    QButtonGroup *photoGroup; // 电子照
    QButtonGroup *educationGroup; // 学历扫描件
    QButtonGroup *idCardGroup; // 身份证扫描件
    QButtonGroup *workGroup; // 工作经历证明
    QButtonGroup *socialGroup; // 工作经历证明
    QButtonGroup *certGroup; // 结业证
};

#endif // MODIFYMATERIALDIALOG_H
