#include "timethread.h"
#include <QDateTime>
#include <QByteArray>
#include <QDataStream>

TimeThread::TimeThread(qintptr socketDescriptor, QObject *parent)
    : QThread (parent), socketDescriptor(socketDescriptor)
{
}

void TimeThread::run()
{
    QTcpSocket tcpSocket;
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) { // 初始化 tcpSocket 类，用于向客户端传回服务器端的当前时间
        emit error(tcpSocket.error());	// 如果出错，则发出 error(tcpSocket.error())信号报告错误
        return;
    }
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    uint time2u = QDateTime::currentDateTime().toTime_t();	// 获取当前时间
    out << time2u;
    tcpSocket.write(block);	// 将获得的当前时间传回客户端
    tcpSocket.disconnectFromHost();	// 断开连接
    tcpSocket.waitForDisconnected();	// 等待返回
}
