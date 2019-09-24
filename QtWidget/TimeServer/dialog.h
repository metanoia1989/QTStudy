#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

class TimeServer;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

public slots:
    void slotShow();	// 用于界面上显示的请求次数

private:
    QLabel *Label1;	// 显示监听端口
    QLabel *Label2;	// 显示请求次数
    QPushButton *quitBtn;	// 退出按钮

    TimeServer *timeServer;	// TCP服务端timeServer
    int count;	// 请求次数计数器 count
};

#endif // DIALOG_H
