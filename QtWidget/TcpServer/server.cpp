#include "server.h"

Server::Server(QObject *parent, int port):QTcpServer (parent)
{
    listen(QHostAddress::Any, port);
}

void Server::incomingConnection(int socketDescriptor)
{
    TcpClientSocket *tcpClientSocket = new TcpClientSocket(this);	// 与客户端通信
    connect(tcpClientSocket, SIGNAL(updateClients(QString, int)),
        this, SLOT(updateClients(int)));	// 连接 TcpClientSocket 的 updateClients 信号
    connect(tcpClientSocket, SIGNAL(disconnected(int)),
        this, SLOT(slotDisconnected(int)));		// 连接 TpcClientSocket 的 disconnected 信号
    tcpClientSocket->setSocketDescriptor(socketDescriptor);
    tcpClientSocketList.append(tcpClientSocket);	// 加入客户端套接字列表方便管理
}

// 将任意客户端发来的信息进行广播，保证聊天室的所有成员均能看到其他人的发言
void Server::updateClients(QString msg, int length)
{
    emit updateServer(msg, length);	// 通知服务器对话框更新响应的显示状态
    for (int i=0;i<tcpClientSocketList.count();i++) {
        // 实现信息的广播
        QTcpSocket *item = tcpClientSocketList.at(i);
        if (item->write(msg.toLatin1(), length)!=length) {
            continue;
        }
    }
}

// 断开所有连接的客户端
void Server::slotDisconnected(int descriptor)
{
    for (int i=0;i<tcpClientSocketList.count();i++) {
        QTcpSocket *item = tcpClientSocketList.at(i);
        if (item->socketDescriptor() == descriptor) {
            tcpClientSocketList.removeAt(i);
            return ;
        }
    }
    return ;
}

