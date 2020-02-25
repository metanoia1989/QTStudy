#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LabSocketState = new QLabel("Socket状态：");
    LabSocketState->setMidLineWidth(200);
    ui->statusbar->addWidget(LabSocketState);

    QString localIP = getLocalIP(); // 本地主机名
    this->setWindowTitle(this->windowTitle() + "----本机IP：" + localIP);

    udpSocket = new QUdpSocket(this);	// 用于与连接的客户端通讯的QTcpSocket
    // Multicast 路由层次，1表示只在同一局域网内
    // 组播TTL：生存时间，每跨1个路由会减1，多播无法跨过大多路由所以为1
    // 默认值是1，表示数据报只能在本地的子网中传送。
    udpSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 1);

    connect(udpSocket, &QUdpSocket::stateChanged, this,
            &MainWindow::onSocketStateChange);
    connect(udpSocket, &QUdpSocket::readyRead, this,
            &MainWindow::onSocketReadyRead);

    onSocketStateChange(udpSocket->state());
}

MainWindow::~MainWindow()
{
    delete udpSocket;
    delete ui;
}

QString MainWindow::getLocalIP()
{
    QString hostName = QHostInfo::localHostName(); // 本地主机名
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    QString localIP = "";

    QList<QHostAddress> addList = hostInfo.addresses();
    if(!addList.isEmpty()) {
        for (int i=0; i<addList.count(); i++) {
            QHostAddress aHost = addList.at(i);
            if (QAbstractSocket::IPv4Protocol == aHost.protocol()) {
                localIP = aHost.toString();
                break;
            }
        }
    }
    return localIP;
}

void MainWindow::onSocketStateChange(QAbstractSocket::SocketState socketState)
{
    switch(socketState)
    {
    case QAbstractSocket::UnconnectedState:
        LabSocketState->setText("scoket状态：UnconnectedState");
        break;
    case QAbstractSocket::HostLookupState:
        LabSocketState->setText("scoket状态：HostLookupState");
        break;
    case QAbstractSocket::ConnectingState:
        LabSocketState->setText("scoket状态：ConnectingState");
        break;

    case QAbstractSocket::ConnectedState:
        LabSocketState->setText("scoket状态：ConnectedState");
        break;

    case QAbstractSocket::BoundState:
        LabSocketState->setText("scoket状态：BoundState");
        break;

    case QAbstractSocket::ClosingState:
        LabSocketState->setText("scoket状态：ClosingState");
        break;

    case QAbstractSocket::ListeningState:
        LabSocketState->setText("scoket状态：ListeningState");
    }
}

// 读取接收到的数据报
void MainWindow::onSocketReadyRead()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());

        QHostAddress peerAddr;
        quint16 peerPort;
        udpSocket->readDatagram(datagram.data(), datagram.size(), &peerAddr, &peerPort);
        QString str = datagram.data();

        QString peer = "[From " + peerAddr.toString() + ":" + QString::number(peerPort) + "] ";

        ui->plainTextEdit->appendPlainText(peer + str);
    }
}

// 加入组播
void MainWindow::on_actStart_triggered()
{
    QString IP = ui->comboIP->currentText();
    groupAddress = QHostAddress(IP); // 多播组地址
    quint16 groupPort = ui->spinPort->value(); // 端口

    // 绑定端口
    if (udpSocket->bind(QHostAddress::AnyIPv4, groupPort, QUdpSocket::ShareAddress)) {
        udpSocket->joinMulticastGroup(groupAddress); // 加入多播组
        ui->plainTextEdit->appendPlainText("**加入组播成功");
        ui->plainTextEdit->appendPlainText("**组播地址IP：" + IP);
        ui->plainTextEdit->appendPlainText("**绑定端口：" + QString::number(groupPort));
        ui->actStart->setEnabled(false);
        ui->actStop->setEnabled(true);
        ui->comboIP->setEnabled(false);
    } else {
        ui->plainTextEdit->appendPlainText("**绑定端口失败");
    }
}

// 退出组播
void MainWindow::on_actStop_triggered()
{
    udpSocket->leaveMulticastGroup(groupAddress); // 退出组播
    udpSocket->abort(); // 解除绑定
    ui->actStart->setEnabled(true);
    ui->actStop->setEnabled(false);
    ui->comboIP->setEnabled(true);
    ui->plainTextEdit->appendPlainText("**已退出组播，解除端口绑定");
}

// 发送组播消息
void MainWindow::on_btnMulticast_clicked()
{

}

// 清空文本框
void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}
