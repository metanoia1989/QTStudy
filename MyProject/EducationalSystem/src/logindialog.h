#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QDialog *parent = nullptr);
    ~LoginDialog();


private slots:
    void on_btn_login_clicked();
    void on_chk_remember_pwd_clicked(bool checked);
    void on_chk_autologin_clicked(bool checked);
    void storeRemember();

private:
    Ui::LoginDialog *ui;

    bool rememberPwd;
    bool autoLogin;
};

#endif // LOGINDIALOG_H
