#include "dialog.h"
#include "./ui_dialog.h"
#include <QNetworkInterface>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

// 通过协议类型返回协议名称
QString Dialog::protocolName(QAbstractSocket::NetworkLayerProtocol protocol)
{
    switch (protocol) {
    case QAbstractSocket::IPv4Protocol:
        return "IPv4 Protocol";
    case QAbstractSocket::IPv6Protocol:
        return "IPv6 Protocol";
    case QAbstractSocket::AnyIPProtocol:
        return "Any IP Protocol";
    default:
        return "Unknown Network Layer Protocol";
    }
}

// QHostInfo获取主机信息
void Dialog::on_btnGetHostInfo_clicked()
{
    QString hostName = QHostInfo::localHostName(); // 本地主机名
    ui->plainTextEdit->appendPlainText("本机主机名: " + hostName + "\n");

    QHostInfo hostInfo = QHostInfo::fromName(hostName); // 本机IP地址
    QList<QHostAddress> addList = hostInfo.addresses(); // IP地址列表

    if (!addList.isEmpty())
    {
        for (int i=0; i<addList.count(); i++)
        {
            QHostAddress aHost = addList.at(i); // 每一项是一个QHostAddress
            bool show = ui->chkOnlyIPv4->isChecked(); // 只显示IPv4
            show =  show ? QAbstractSocket::IPv4Protocol == aHost.protocol() : true;
            if (show)
            {
                ui->plainTextEdit->appendPlainText("协 议：" + protocolName(aHost.protocol())); // 协议类型
                ui->plainTextEdit->appendPlainText("本机IP地址：" + aHost.toString()); // IP地址
                ui->plainTextEdit->appendPlainText("\n");
            }
        }
    }
}

// 查找主机信息
void Dialog::on_btnLookup_clicked()
{
    QString hostname = ui->editHost->text(); // 主机名
    ui->plainTextEdit->appendPlainText("正在查找主机信息：" + hostname);
    QHostInfo::lookupHost(hostname, this, &Dialog::lookedUpHostInfo);
}

// 查找主机信息槽函数
void Dialog::lookedUpHostInfo(const QHostInfo &host)
{
    QList<QHostAddress> addList = host.addresses();
    if (!addList.isEmpty())
    {
        for (int i=0; i<addList.count(); i++)
        {
            QHostAddress aHost = addList.at(i); // 每一项是一个QHostAddress
            bool show = ui->chkOnlyIPv4->isChecked(); // 只显示IPv4
            show =  show ? QAbstractSocket::IPv4Protocol == aHost.protocol() : true;
            if (show)
            {
                ui->plainTextEdit->appendPlainText("协 议：" + protocolName(aHost.protocol())); // 协议类型
                ui->plainTextEdit->appendPlainText("本机IP地址：" + aHost.toString()); // IP地址
                ui->plainTextEdit->appendPlainText("\n");
            }
        }
    }
}

// QNetworkInterface::allAddresses()函数的使用
void Dialog::on_btnDetail_clicked()
{
    QList<QHostAddress> addList = QNetworkInterface::allAddresses();
    if (!addList.isEmpty())
    {
        for (int i=0; i<addList.count(); i++)
        {
            QHostAddress aHost = addList.at(i); // 每一项是一个QHostAddress
            bool show = ui->chkOnlyIPv4->isChecked(); // 只显示IPv4
            show =  show ? QAbstractSocket::IPv4Protocol == aHost.protocol() : true;
            if (show)
            {
                ui->plainTextEdit->appendPlainText("协 议：" + protocolName(aHost.protocol())); // 协议类型
                ui->plainTextEdit->appendPlainText("本机IP地址：" + aHost.toString()); // IP地址
                ui->plainTextEdit->appendPlainText("\n");
            }
        }
    }
}

// QNetworkInterface::allInterfaces()函数的使用
void Dialog::on_btnAllInterface_clicked()
{
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    for (int i=0; i<list.count(); i++)
    {
        QNetworkInterface aInterface = list.at(i);
        if (!aInterface.isValid())
            continue;
        ui->plainTextEdit->appendPlainText("设备名称：" + aInterface.humanReadableName());
        ui->plainTextEdit->appendPlainText("硬件地址：" + aInterface.hardwareAddress());

        QList<QNetworkAddressEntry> entryList = aInterface.addressEntries();
        for (int j=0; j<entryList.count(); j++)
        {
            QNetworkAddressEntry aEntry = entryList.at(j);
            ui->plainTextEdit->appendPlainText("	IP地址：" + aEntry.ip().toString());
            ui->plainTextEdit->appendPlainText("	子网掩码：" + aEntry.netmask().toString());
            ui->plainTextEdit->appendPlainText("	广播地址：" + aEntry.broadcast().toString());
        }
        ui->plainTextEdit->appendPlainText("\n");
    }
}

void Dialog::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}
