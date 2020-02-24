#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LabListen = new QLabel("监听状态：");
    LabListen->setMinimumWidth(150);
    ui->statusbar->addWidget(LabListen);

    LabSocketState = new QLabel("Socket状态：");
    LabSocketState->setMidLineWidth(200);
    ui->statusbar->addWidget(LabSocketState);

    QString localIP = getLocalIP(); // 本机IP
    this->setWindowTitle(this->windowTitle() + "---本机IP：" + localIP);
    ui->comboIP->addItem(localIP);

    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this,
            &MainWindow::onNewConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 获取本机IPv4地址
QString MainWindow::getLocalIP()
{
    QString hostName = QHostInfo::localHostName(); // 本机主机名
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
    }
    return localIP;
}

// 关闭窗口时停止监听
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (tcpServer->isListening()) {
        tcpServer->close(); // 停止
    }
    event->accept();
}

// 有新的客户端连接
void MainWindow::onNewConnection()
{
    tcpSocket = tcpServer->nextPendingConnection(); // 创建 socket
    connect(tcpSocket, &QTcpSocket::connected, this,
            &MainWindow::onClientConnected);
    connect(tcpSocket, &QTcpSocket::disconnected, this,
            &MainWindow::onClientDisconnected);
    connect(tcpSocket, &QTcpSocket::stateChanged, this,
            &MainWindow::onSocketStateChange);
    connect(tcpSocket, &QTcpSocket::readyRead, this,
            &MainWindow::onSocketReadyRead);
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

// 客户端接入
void MainWindow::onClientConnected()
{
    ui->plainTextEdit->appendPlainText("**client socket connected");
    ui->plainTextEdit->appendPlainText("**peer address:" +
                                       tcpSocket->peerAddress().toString());
    ui->plainTextEdit->appendPlainText("**peer port:" +
                                       QString::number(tcpSocket->peerPort()));
}

// 客户端断开连接
void MainWindow::onClientDisconnected()
{
    ui->plainTextEdit->appendPlainText("**client socket disconnected");
    tcpSocket->deleteLater();
}

// 读取缓冲区行文本
void MainWindow::onSocketReadyRead()
{
    while (tcpSocket->canReadLine()) {
        ui->plainTextEdit->appendPlainText("[in] " + tcpSocket->readLine());
    }
}

// 开始监听
void MainWindow::on_actStart_triggered()
{
    QString IP = ui->comboIP->currentText(); // IP地址
    quint16 port = ui->spinPort->value(); // 端口
    QHostAddress addr(IP);
    tcpServer->listen(addr, port);

    ui->plainTextEdit->appendPlainText("**开始监听...");
    ui->plainTextEdit->appendPlainText("**服务器地址："
                   + tcpServer->serverAddress().toString());
    ui->plainTextEdit->appendPlainText("**服务器端口："
                   + QString::number(tcpServer->serverPort()));
    ui->actStart->setEnabled(false);
    ui->actStop->setEnabled(true);
    LabListen->setText("监听状态：正在监听");
}

// 停止监听
void MainWindow::on_actStop_triggered()
{
    if (tcpServer->isListening()) { // TcpServer正在监听
        tcpServer->close(); // 停止监听
        ui->actStart->setEnabled(true);
        ui->actStop->setEnabled(true);
        LabListen->setText("监听状态：已停止监听");
    }
}

// 清空文本框
void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}

// 获取本机地址
void MainWindow::on_actHostInfo_triggered()
{
    QString hostName = QHostInfo::localHostName(); // 本机主机名
    ui->plainTextEdit->appendPlainText("本机主机名：" + hostName + "\n");
    QHostInfo hostInfo = QHostInfo::fromName(hostName);

    QList<QHostAddress> addList = hostInfo.addresses();
}

// 发送一行消息
void MainWindow::on_btnSend_clicked()
{
    QString msg = ui->editMsg->text();
    ui->plainTextEdit->appendPlainText("[out] " + msg);
    ui->editMsg->clear();
    ui->editMsg->setFocus();

    QByteArray str = msg.toUtf8();
    str.append("\n"); // 添加一个换行符
    tcpSocket->write(str);
}
