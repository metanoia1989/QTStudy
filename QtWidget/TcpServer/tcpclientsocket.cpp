#include "tcpclientsocket.h"

TcpClientSocket::TcpClientSocket(QObject *parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(dataReceived()));	// 有数据到来时发送信号
    connect(this, SIGNAL(disconnected()), this, SLOT(dataReceived()));	// 在断开连接时发送信
}

void TcpClientSocket::dataReceived()
{
    while (bytesAvailable()>0) {	// 有数据到来时将有效数据取出
        int length = bytesAvailable();
        char buf[1024];
        read(buf, length);
        QString msg = buf;
        emit updateClients(msg, length);	// 通知服务器向聊天室内的所有成员广播消息
    }
}

void TcpClientSocket::slotDisconnected()
{
    emit disconnected(this->socketDescriptor());
}
