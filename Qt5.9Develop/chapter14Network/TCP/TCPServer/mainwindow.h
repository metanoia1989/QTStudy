#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
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

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    // 自定义槽函数
    void onNewConnection(); // QTcpServer的newConnection() 信号
    void onSocketStateChange(QAbstractSocket::SocketState socketState);
    void onClientConnected(); // Client Socket connected
    void onClientDisconnected(); // Client Socket disconnected
    void onSocketReadyRead(); // 读取socket传入的数据

    void on_actStart_triggered();

    void on_actStop_triggered();

    void on_actClear_triggered();

    void on_actHostInfo_triggered();

    void on_btnSend_clicked();

private:
    Ui::MainWindow *ui;
    QLabel *LabListen; // 状态栏标签
    QLabel *LabSocketState; // 状态栏标签
    QTcpServer *tcpServer; // TCP服务器
    QTcpSocket *tcpSocket; // TCP通讯的Socket
    QString getLocalIP(); // 获取本机IP地址
};
#endif // MAINWINDOW_H
