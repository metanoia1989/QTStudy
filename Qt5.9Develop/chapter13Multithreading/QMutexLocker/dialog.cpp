#include "dialog.h"
#include "./ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(&threadA, &QThread::started, this,
            &Dialog::onthreadA_started);
    connect(&threadA, &QThread::finished, this,
            &Dialog::onthreadA_finished);
    connect(&mTimer, &QTimer::timeout, this, &Dialog::onTimeOut);
}

Dialog::~Dialog()
{
    delete ui;
}

// 窗口关闭事件，必须结束线程
void Dialog::closeEvent(QCloseEvent *event)
{
    if (threadA.isRunning()) {
        threadA.stopThread();
        threadA.wait();
    }
    event->accept();
}

// 线程started()信号的响应槽函数
void Dialog::onthreadA_started()
{
    ui->LabA->setText("Thread状态：thread started");
}

// 线程的finished()信号的响应槽函数
void Dialog::onthreadA_finished()
{
    ui->LabA->setText("Thread状态：thread finished");
}

// 定时器到时处理槽函数
void Dialog::onTimeOut()
{
    int tmpSeq = 0, tmpValue = 0;
    bool valid = threadA.readValue(&tmpSeq, &tmpValue);	// 读取数据
    if (valid && (tmpSeq != mSeq)) { // 有效并且是新数据
        mSeq = tmpSeq;
        mDiceValue = tmpValue;
        QString str = QString::asprintf("第 %d 次掷骰子，点数为：%d", mSeq, mDiceValue);
        ui->plainTextEdit->appendPlainText(str);
        QPixmap pic; // 图片显示
        QString filename = QString::asprintf(":/dice/images/d%d.jpg", mDiceValue);
        pic.load(filename);
        ui->LabPic->setPixmap(pic);
    }
}

// 启动线程按钮
void Dialog::on_btnStartThread_clicked()
{
    mSeq = 0;
    threadA.start();

    ui->btnStartThread->setEnabled(false);
    ui->btnStopThread->setEnabled(true);

    ui->btnDiceBegin->setEnabled(true);
    ui->btnDiceEnd->setEnabled(false);
}

// 结束线程按钮
void Dialog::on_btnStopThread_clicked()
{
    threadA.stopThread();	// 结束线程的run()函数执行
    threadA.wait();

    ui->btnStartThread->setEnabled(true);
    ui->btnStopThread->setEnabled(false);

    ui->btnDiceBegin->setEnabled(false);
    ui->btnDiceEnd->setEnabled(false);

}

// 清空文本按钮
void Dialog::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}

// 开始掷骰子按钮
void Dialog::on_btnDiceBegin_clicked()
{
    threadA.diceBegin();
    mTimer.start(100);	// 每100ms读取一次数据
    ui->btnDiceBegin->setEnabled(false);
    ui->btnDiceEnd->setEnabled(true);
}

// 暂停掷骰子按钮
void Dialog::on_btnDiceEnd_clicked()
{
    threadA.dicePause();
    mTimer.stop();
    ui->btnDiceBegin->setEnabled(true);
    ui->btnDiceEnd->setEnabled(false);
}
