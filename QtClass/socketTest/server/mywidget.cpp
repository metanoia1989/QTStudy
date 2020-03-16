#include "mywidget.h"
#include "ui_mywidget.h"
#include "comm.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget),
    comm(NULL)
{
    ui->setupUi(this);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_clicked() // 启动通信
{
    if (comm == NULL)
    {
        comm = Comm::getComm(); // 通信
        connect(this,&MyWidget::startCommSend,comm,&Comm::commSend);    // 启动线程发送数据
        connect(comm, &Comm::connect_ok, this, &MyWidget::getCommOk);   // 通信连接成功
        connect(comm, &Comm::comm_receive, this, &MyWidget::getCommReceive); // 获取硬件发送信息
        qDebug() << "启动通信服务";
    }
}

void MyWidget::on_pushButton_2_clicked() // 停止通信
{
    if (comm)
    {
        comm->stopComm();
        comm = NULL;
        qDebug() << "断开客户端连接";
    }
}

// 获取硬件发送的数据
void MyWidget::getCommReceive(QByteArray recData)
{
    QString str = recData;
    qDebug() << str;
}

void MyWidget::getCommOk() // 获取连接状态
{
    qDebug() << "连接成功";
}
