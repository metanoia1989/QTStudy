#ifndef THREADDLG_H
#define THREADDLG_H

#include <QDialog>
#include <QPushButton>
#include "workthread.h"
#define MAXSIZE 1	// 宏 定义线程数目

class ThreadDlg : public QDialog
{
    Q_OBJECT

public:
    ThreadDlg(QWidget *parent = nullptr);
    ~ThreadDlg();

public slots:
    void slotStart();	// 槽函数用于启动线程
    void slotStop();	// 槽函数用于终止线程

private:
    QPushButton *startBtn;
    QPushButton *stopBtn;
    QPushButton *quitBtn;
    WorkThread *wordThread[MAXSIZE];	// 指向工作线程的私有指针数组
};

#endif // THREADDLG_H
