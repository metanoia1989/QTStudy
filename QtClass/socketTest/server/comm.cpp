#include "comm.h"

Comm::Comm(QObject *parent) : QObject(parent),tcpServer(NULL),tcpSocket(NULL)
{
    if (tcpServer == NULL)
    {
        tcpServer = new QTcpServer(this); // 监听套接字
    }
    tcpServer->listen(QHostAddress::Any, 8086);
    // 客户端连接
    connect(tcpServer,&QTcpServer::newConnection,[=](){
        tcpSocket = tcpServer->nextPendingConnection(); // 取出建立好的套接字

        // 获取对方的IP和端口
        QString ip = tcpSocket->peerAddress().toString();
        qint16 port = tcpSocket->peerPort();
        qDebug() << "连接成功";
        qDebug() << ip << ":" << port;
        emit connect_ok(); // 连接成功...
        // 客户端发送过来消息
        connect(tcpSocket, &QTcpSocket::readyRead,this,&Comm::commRead,Qt::UniqueConnection);
    });
}

Comm* Comm::getComm() // 获取通信对象
{
    static Comm comm;
    return &comm;
}

void Comm::commSend(QString sendData) // 发送数据
{
    if (tcpSocket)
    {
        tcpSocket->write(sendData.toUtf8().data()); // 发送数据
    }
}
void Comm::commRead() // 获取客户端数据
{
    qDebug() << tcpSocket;
    QByteArray array = tcpSocket->readAll(); // 获取客户端发送的数据
    emit comm_receive(array);
}

void Comm::stopComm() // 断开连接
{
    if (tcpSocket)
    {
        // 断开信号和槽的连接
        QString ip = tcpSocket->peerAddress().toString();
        qint16 port = tcpSocket->peerPort();
        qDebug() << "连接断开";
        qDebug() << ip << ":" << port;

        tcpSocket->disconnectFromHost(); // 断开连接
        tcpSocket->close();
        disconnect(tcpSocket, &QTcpSocket::readyRead,this,&Comm::commRead);
        tcpSocket = NULL;
    }
}

Comm::~Comm()
{
    if (tcpServer)
    {
        delete tcpServer;
        tcpServer = NULL;
    }
}
