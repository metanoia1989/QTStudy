#ifndef COMM_H
#define COMM_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Comm : public QObject
{
    Q_OBJECT
public:
    ~Comm();
    static Comm* getComm();
    void stopComm(); // 断开连接
    // 发送数据
    void commSend(QString sendData);

signals:
    void connect_ok();
    void comm_receive(QByteArray);

public slots:
    void commRead(); // 获取客户端数据
private:
    Comm(QObject *parent = nullptr);
    QTcpServer *tcpServer; // 监听套接字
    QTcpSocket *tcpSocket; // 通信套接字
};

#endif // COMM_H


