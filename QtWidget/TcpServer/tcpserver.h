#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QDialog>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include "server.h"

class TcpServer : public QDialog
{
    Q_OBJECT

public:
    TcpServer(QWidget *parent = nullptr, Qt::WindowFlags f=nullptr);
    ~TcpServer();

public slots:
    void slotCreateServer();
    void updateServer(QString, int);

private:
    QListWidget *ContentListWidget;
    QLabel *PortLabel;
    QLineEdit *PortLineEidt;
    QPushButton *CreateBtn;
    QGridLayout *mainLayout;

    int port;
    Server *server;
};

#endif // TCPSERVER_H
