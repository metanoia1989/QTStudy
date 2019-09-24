#include "timeserver.h"
#include "timethread.h"
#include "dialog.h"

TimeServer::TimeServer(QObject *parent):QTcpServer (parent)
{
    dlg = static_cast<Dialog*>(parent);
}

// 重写虚函数 incomingConnection()
void TimeServer::incomingConnection(qintptr socketDescriptor)
{
    TimeThread *thread = new TimeThread(socketDescriptor, nullptr);	// 创建工作线程
    connect(thread, SIGNAL(finished()), dlg, SLOT(slotShow()));	// 线程创建完成消息关联slotShow用于显示请求计数
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()), Qt::DirectConnection);	// 用于结束线程
    thread->start();
}
