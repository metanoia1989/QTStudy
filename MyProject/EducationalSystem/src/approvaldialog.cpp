#include "approvaldialog.h"
#include "ui_approvaldialog.h"

ApprovalDialog::ApprovalDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApprovalDialog)
{
    ui->setupUi(this);

    approvalGroup = new QButtonGroup(this);
    approvalGroup->addButton(ui->radioPass, 1);
    approvalGroup->addButton(ui->radioReject, 2);
}

ApprovalDialog::~ApprovalDialog()
{
    delete ui;
}

int ApprovalDialog::getResult()
{
    return approvalGroup->checkedId();
}

void ApprovalDialog::clearChecked()
{
    QAbstractButton *checked = approvalGroup->checkedButton();
    if (checked) {
        approvalGroup->setExclusive(false);
        checked->setChecked(false);
        approvalGroup->setExclusive(true);
    }
}
