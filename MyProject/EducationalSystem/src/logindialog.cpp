#include "logindialog.h"
#include "ui_logindialog.h"
#include "utils/global.h"
#include "utils/token.h"
#include <QMessageBox>
#include <QDebug>


LoginDialog::LoginDialog(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    rememberPwd = Global::cache()->getItem("rememberPwd").toInt() == 1;
    autoLogin = Global::cache()->getItem("autoLogin").toInt() == 1;

    if (rememberPwd) {
        ui->edit_username->setText(Global::cache()->getItem("username"));
        ui->edit_password->setText(Global::cache()->getItem("password"));
        ui->chk_remember_pwd->setChecked(true);
    }


    connect(this, &QDialog::accepted, this, &LoginDialog::storeRemember);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

/**
 * @brief 登录完毕后记录用户名密码
 */
void LoginDialog::storeRemember()
{
    if (rememberPwd) {
        Global::cache()->setItem("username", ui->edit_username->text().trimmed());
        Global::cache()->setItem("password", ui->edit_password->text().trimmed());
    }
    Global::cache()->setItem("rememberPwd", rememberPwd ? "1" : "0");
    Global::cache()->setItem("autoLogin", autoLogin ? "1" : "0");
}

void LoginDialog::on_btn_login_clicked()
{
    ui->btn_login->setEnabled(false);
    QString username = ui->edit_username->text().trimmed();
    QString password = ui->edit_password->text().trimmed();
    if (username.isEmpty() || password.isEmpty()) {
        auto msgBox = new QMessageBox(this);
        msgBox->setWindowTitle("请求出错");
        msgBox->setIcon(QMessageBox::Critical);
        msgBox->setText("用户名或密码不能为空");
        msgBox->exec();
        ui->btn_login->setEnabled(true);
        return;
    }

    Token::setUsername(username);
    Token::setPasswd(password);
    QString strToken = Token::token();
    qDebug() << "拿到的Token 值为：" << strToken;
    if (Token::lastIsNetworkError()) {
        auto msgBox = new QMessageBox(this);
        msgBox->setWindowTitle("请求出错");
        msgBox->setIcon(QMessageBox::Critical);
        msgBox->setText(Token::lastErrorMessage());
        msgBox->exec();
        ui->btn_login->setEnabled(true);
    } else {
        Global::cache()->setItem("token", strToken);
        QDialog::accept();
    }

}

void LoginDialog::on_chk_remember_pwd_clicked(bool checked)
{
    if (!checked) {
        autoLogin = false;
        ui->chk_autologin->setChecked(false);
    }
    rememberPwd = checked;
}

void LoginDialog::on_chk_autologin_clicked(bool checked)
{
    if (checked) {
        rememberPwd = true;
        ui->chk_remember_pwd->setChecked(true);
    }
    autoLogin = checked;
}
