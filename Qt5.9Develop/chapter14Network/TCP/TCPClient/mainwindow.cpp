#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QHostAddress>
#include <QHostInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tcpClient = new QTcpSocket(this);	// 创建socket变量

    LabSocketState = new QLabel("Socket状态：");	// 状态栏标签
    LabSocketState->setMinimumWidth(250);
    ui->statusbar->addWidget(LabSocketState);

    QString localIP = getLocalIP(); // 本机IP
    this->setWindowTitle(this->windowTitle() + "----本机IP：" + localIP);
    ui->comboServer->addItem(localIP);

    connect(tcpClient, &QTcpSocket::connected, this,
            &MainWindow::onConnected);
    connect(tcpClient, &QTcpSocket::disconnected, this,
            &MainWindow::onDisconnected);
    connect(tcpClient, &QTcpSocket::stateChanged, this,
            &MainWindow::onSocketStateChange);
    connect(tcpClient, &QTcpSocket::readyRead, this,
            &MainWindow::onSocketReadyRead);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (tcpClient->state() == QAbstractSocket::ConnectedState) {
        tcpClient->disconnectFromHost();
    }
    event->accept();
}

QString MainWindow::getLocalIP()
{
    QString hostName = QHostInfo::localHostName();	// 本机主机名
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    QString localIP = "";

    QList<QHostAddress> addList = hostInfo.addresses();
    if (!addList.isEmpty()) {
        for (int i=0; i<addList.count(); i++) {
            QHostAddress aHost = addList.at(i);
            if (QAbstractSocket::IPv4Protocol == aHost.protocol()) {
                localIP = aHost.toString();
                break;
            }
        }
        return localIP;
    }
}

// connected() 信号槽函数
void MainWindow::onConnected()
{
    ui->plainTextEdit->appendPlainText("**已连接到服务器.");
    ui->plainTextEdit->appendPlainText("**peer address: " +
                                       tcpClient->peerAddress().toString());
    ui->plainTextEdit->appendPlainText("**peer port: "+
                                       QString::number(tcpClient->peerPort()));
    ui->actConnect->setEnabled(false);
    ui->actDisconnect->setEnabled(true);
}

// disConnected() 信号槽函数
void MainWindow::onDisconnected()
{
    ui->plainTextEdit->appendPlainText("**已断开与服务器的连接");
    ui->actConnect->setEnabled(true);
    ui->actDisconnect->setEnabled(false);
}

// readyRead() 信号槽函数
void MainWindow::onSocketReadyRead()
{
    while (tcpClient->canReadLine()) {
        ui->plainTextEdit->appendPlainText("[in] " + tcpClient->readLine());
    }
}

// socket 状态变化
void MainWindow::onSocketStateChange(QAbstractSocket::SocketState socketState)
{
    switch (socketState) {
    case QAbstractSocket::UnconnectedState:
        LabSocketState->setText("socket状态：UnconnectedState");
        break;
    case QAbstractSocket::HostLookupState:
        LabSocketState->setText("socket状态：HostLookupState");
        break;
    case QAbstractSocket::ConnectingState:
        LabSocketState->setText("socket状态：ConnectingState");
        break;
    case QAbstractSocket::ConnectedState:
        LabSocketState->setText("socket状态：ConnectedState");
        break;
    case QAbstractSocket::BoundState:
        LabSocketState->setText("socket状态：BoundState");
        break;
    case QAbstractSocket::ClosingState:
        LabSocketState->setText("socket状态：ClosingState");
        break;
    case QAbstractSocket::ListeningState:
        LabSocketState->setText("socket状态：ListeningState");
    }
}

// 连接到服务器
void MainWindow::on_actConnect_triggered()
{
    QString addr = ui->comboServer->currentText();
    quint16 port = ui->spinPort->value();
    tcpClient->connectToHost(addr, port);
}

// 断开与服务器的连接
void MainWindow::on_actDisconnect_triggered()
{
    if (tcpClient->state() == QAbstractSocket::ConnectedState) {
        tcpClient->disconnectFromHost();
    }
}

// 清除文本框
void MainWindow::on_actQuit_triggered()
{
    ui->plainTextEdit->clear();
}

// 发送消息
void MainWindow::on_btnSend_clicked()
{
    QString msg = ui->editMsg->text();
    ui->plainTextEdit->appendPlainText("[out] " + msg);
    ui->editMsg->clear();
    ui->editMsg->setFocus();

    QByteArray str = msg.toUtf8();
    str.append("\n");
    tcpClient->write(str);
}
