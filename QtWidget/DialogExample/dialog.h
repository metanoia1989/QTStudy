#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include "inputdlg.h"
#include "msgboxdlg.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QGridLayout *mainLayout;
    // 文件对话框
    QPushButton *fileBtn;
    QLineEdit *fileLineEdit;
    // 颜色对话框
    QPushButton *colorBtn;
    QFrame *colorFrame;
    // 字体对话框
    QPushButton *fontBtn;
    QLineEdit *fontLineEdit;
    // 标准输入框
    QPushButton *inputBtn;
    InputDlg *inputDlg;
    // 消息对话框类
    QPushButton *MsgBtn;
    MsgBoxDlg *msgDlg;
    // 自定义消息框
    QPushButton *CustomBtn;
    QLabel *label;

private slots:
    void showFile();
    void showColor();
    void showFont();
    void showInputDlg();
    void showMsgDlg();
    void showCustomDlg();
};

#endif // DIALOG_H
