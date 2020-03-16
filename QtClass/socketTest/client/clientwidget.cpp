#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QHostAddress>
ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, &QTcpSocket::connected,[=]()
    {
        ui->textEdit->setText("连接成功");
    });

    connect(tcpSocket,&QTcpSocket::readyRead,[=]()
    {
        QByteArray array = tcpSocket->readAll();
        QString str = array;
        ui->textEdit->append(str);
    });
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_pushButton_clicked()
{
    QString ip = ui->lineEdit->text();
    qint16 port = ui->lineEdit_2->text().toInt();
    tcpSocket->abort();
    tcpSocket->connectToHost(QHostAddress(ip),port);
}

void ClientWidget::on_pushButton_2_clicked()
{
    QString str = ui->textEdit_2->toPlainText(); // 获取发送的内容
    // 发送数据给对方
    if (tcpSocket)
        tcpSocket->write(str.toUtf8().data());
}
