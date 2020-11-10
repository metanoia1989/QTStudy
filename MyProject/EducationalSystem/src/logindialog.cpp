#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_btn_login_clicked()
{
    QDialog::accept();
}
