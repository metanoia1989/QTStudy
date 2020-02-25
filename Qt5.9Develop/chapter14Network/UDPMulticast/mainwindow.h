#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 自定义槽函数
    void onSocketStateChange(QAbstractSocket::SocketState socketState);
    void onSocketReadyRead();	// 读取 socket 传入的数据

    void on_actStart_triggered();

    void on_actStop_triggered();

    void on_btnMulticast_clicked();

    void on_actClear_triggered();

private:
    QString getLocalIP();	// 获取本机IP地址

    Ui::MainWindow *ui;
    QLabel *LabSocketState;
    QUdpSocket *udpSocket;	// 用于与连接的客户端通讯的QTcpSocket
    QHostAddress groupAddress; // 组播地址
};
#endif // MAINWINDOW_H
