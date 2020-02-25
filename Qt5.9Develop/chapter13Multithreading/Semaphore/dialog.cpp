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
    connect(&threadConsumer, &QThreadShow::newValue, this, &Dialog::onthreadB_newValue);
}

Dialog::~Dialog()
{
    delete ui;
}

// 窗口关闭事件，必须结束线程
void Dialog::closeEvent(QCloseEvent *event)
{
    if (threadProducer.isRunning()) {
        threadProducer.terminate();
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

// 读取threadConsumer传递的缓冲区的数据
void Dialog::onthreadB_newValue(int *data, int count, int bufNo)
{
    QString str = QString::asprintf("第 %d 个缓冲区", bufNo);
    for (int i=0; i<count; i++) {
        str += QString::asprintf("%d, ", *data);
        data++;
    }
    str += "\n";
    ui->plainTextEdit->appendPlainText(str);
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
    threadProducer.terminate();	// 结束线程的run()函数执行
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
