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

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
