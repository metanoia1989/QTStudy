#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QHostInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    // 查找主机信息槽函数
    void lookedUpHostInfo(const QHostInfo &host);

    void on_btnGetHostInfo_clicked();

    void on_btnLookup_clicked();

    void on_btnDetail_clicked();

    void on_btnAllInterface_clicked();

    void on_btnClear_clicked();

private:
    // 通过协议类型返回协议名称
    QString protocolName(QAbstractSocket::NetworkLayerProtocol protocol);

    Ui::Dialog *ui;
};
#endif // DIALOG_H
