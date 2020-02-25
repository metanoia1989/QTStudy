#include "dialog.h"
#include "./ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(&threadProducer, &QThread::started, this, &Dialog::onthreadA_started);
    connect(&threadProducer, &QThread::finished, this, &Dialog::onthreadA_finished);
    connect(&threadConsumer, &QThread::started, this, &Dialog::onthreadB_started);
    connect(&threadConsumer, &QThread::finished, this, &Dialog::onthreadB_finished);
    connect(&threadConsumer, &QThreadConsumer::newValue, this, &Dialog::onthreadB_newValue);
}

Dialog::~Dialog()
{
    delete ui;
}

// 窗口关闭事件，必须结束线程
void Dialog::closeEvent(QCloseEvent *event)
{
    if (threadProducer.isRunning()) {
        threadProducer.stopThread();
        threadProducer.wait();
    }
    if (threadConsumer.isRunning()) {
        threadConsumer.terminate();
        threadConsumer.wait();
    }
    event->accept();
}

void Dialog::onthreadA_started()
{
    ui->LabA->setText("Thread Producer状态：started");
}

void Dialog::onthreadA_finished()
{
    ui->LabA->setText("Thread Producer状态：finished");
}

void Dialog::onthreadB_started()
{
    ui->LabB->setText("Thread Consumer：started");
}

void Dialog::onthreadB_finished()
{
    ui->LabB->setText("Thread Consumer：finished");
}

void Dialog::onthreadB_newValue(int seq, int diceValue)
{
    QString str = QString::asprintf("第 %d 次掷骰子，点数为：%d", seq, diceValue);
    ui->plainTextEdit->appendPlainText(str);
    QPixmap pic; // 图片显示
    QString filename = QString::asprintf(":/dice/images/d%d.jpg", diceValue);
    pic.load(filename);
    ui->LabPic->setPixmap(pic);
}

// 启动线程按钮
void Dialog::on_btnStartThread_clicked()
{
    ui->btnStartThread->setEnabled(false);
    ui->btnStopThread->setEnabled(true);

    threadConsumer.start(); // 先启动，避免丢失第一次掷骰子数据
    threadProducer.start();
}

// 结束线程按钮
void Dialog::on_btnStopThread_clicked()
{
    threadProducer.stopThread();	// 结束线程的run()函数执行
    threadProducer.wait();

    threadConsumer.terminate(); // 因为threadB可能处于等待状态，用terminate强制结束
    threadConsumer.wait();

    ui->btnStartThread->setEnabled(true);
    ui->btnStopThread->setEnabled(false);
}

// 清空文本按钮
void Dialog::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}
