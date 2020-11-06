#include "delegatetableviewdialog.h"
#include "ui_delegatetableviewdialog.h"
#include "mydelegate.h"

DelegateTableViewDialog::DelegateTableViewDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DelegateTableViewDialog)
{
    ui->setupUi(this);

    myDelegate = new MyDelegate(this);

    model = new QStandardItemModel(4, 2, this);
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(myDelegate);

    // 填充数据
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 2; col++) {
            auto index = model->index(row, col, QModelIndex());
            model->setData(index, 0);
        }
    }
}

DelegateTableViewDialog::~DelegateTableViewDialog()
{
    delete ui;
}

