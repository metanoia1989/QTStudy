#include "threaddlg.h"
#include <QHBoxLayout>

ThreadDlg::ThreadDlg(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("线程"));
    startBtn = new QPushButton(tr("开始"));
    stopBtn = new QPushButton(tr("停止"));
    quitBtn = new QPushButton(tr("退出"));
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(startBtn);
    mainLayout->addWidget(stopBtn);
    mainLayout->addWidget(quitBtn);

    connect(startBtn, SIGNAL(clicked()), this, SLOT(slotStart()));
    connect(stopBtn, SIGNAL(clicked()), this, SLOT(slotStop()));
    connect(quitBtn, SIGNAL(clicked()), this, SLOT(close()));
}

ThreadDlg::~ThreadDlg()
{

}

// 使新建的线程尽可能同时开始执行
void ThreadDlg::slotStart()
{
    for (int i=0;i<MAXSIZE;i++) {
        wordThread[i] = new WorkThread(); // 创建线程，将其指针保存在数组中
    }
    for (int i=0;i<MAXSIZE;i++) {
        wordThread[i]->start(); 	// 启动线程
    }
    startBtn->setEnabled(false);
    stopBtn->setEnabled(true);
}


void ThreadDlg::slotStop()
{
    for (int i=0;i<MAXSIZE;i++) {
        wordThread[i]->terminate();	 // 终止线程
        wordThread[i]->wait();	// 线程阻塞等待直到退出或超时
    }
    startBtn->setEnabled(true);
    stopBtn->setEnabled(false);
}
