#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
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
    void onConnected();
    void onDisconnected();
    void onSocketStateChange(QAbstractSocket::SocketState socketState);
    void onSocketReadyRead();	// 读取socket传入的数据

    void on_actConnect_triggered();

    void on_actDisconnect_triggered();

    void on_actQuit_triggered();

    void on_btnSend_clicked();

private:
    QString getLocalIP();	// 获取本机地址

    Ui::MainWindow *ui;
    QTcpSocket *tcpClient; // socket
    QLabel *LabSocketState; // 状态栏显示标签
};
#endif // MAINWINDOW_H
