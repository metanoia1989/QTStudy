#ifndef APPROVALDIALOG_H
#define APPROVALDIALOG_H

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class ApprovalDialog;
}

class ApprovalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ApprovalDialog(QWidget *parent = nullptr);
    ~ApprovalDialog();

    int getResult();
    void clearChecked();

private:
    Ui::ApprovalDialog *ui;

    QButtonGroup *approvalGroup;
};

#endif // APPROVALDIALOG_H
