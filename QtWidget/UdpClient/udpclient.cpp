#include "udpclient.h"
#include <QMessageBox>
#include <QHostAddress>

UdpClient::UdpClient(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("UDP Client"));
    /* 初始化各个控件 */
    ReceiveTextEdit = new QTextEdit(this);
    CloseBtn = new QPushButton(tr("Close"), this);
    /* 设置布局 */
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(ReceiveTextEdit);
    mainLayout->addWidget(CloseBtn);

    connect(CloseBtn, SIGNAL(clicked()), this, SLOT(CloseBtnClicked()));
    port = 5555;	// 设置UDP的端口参数，指定在此端口上监听数据
    udpSocket = new QUdpSocket(this);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(dataReceived()));

    bool result = udpSocket->bind(port);
    if (!result) {
        QMessageBox::information(this, tr("error"), tr("udp socket create error!"));
        return ;
    }
}

UdpClient::~UdpClient()
{

}

void UdpClient::CloseBtnClicked()
{
    close();
}

// 将UdpSocket 对象中的可读数据读出并显示
void UdpClient::dataReceived()
{
    while (udpSocket->hasPendingDatagrams()) {	// 判断UdpSocket中是否有数据报可读
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size()); // 获取一个数据报的长度
        QString msg = datagram.data();
        ReceiveTextEdit->insertPlainText(msg);
    }
}
