#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class Dialog;

class TimeServer : public QTcpServer
{
    Q_OBJECT
public:
    TimeServer(QObject *parent=nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    Dialog *dlg;
};

#endif // TCPSERVER_H
