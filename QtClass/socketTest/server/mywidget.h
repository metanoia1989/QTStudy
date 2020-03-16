#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class Comm;
namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();
signals:
    void startCommSend(QString); // 发送数据
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void getCommReceive(QByteArray recData); // 获取数据
    void getCommOk(); // 获取连接状态

private:
    Ui::MyWidget *ui;
    Comm *comm; // 通信模块
};

#endif // MYWIDGET_H
