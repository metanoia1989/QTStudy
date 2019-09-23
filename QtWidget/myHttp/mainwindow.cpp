#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this,
        SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("http://www.baidu.com")));

    ui->progressBar->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::replyFinished(QNetworkReply *reply)
{
    QString all = reply->readAll();
    ui->textBrowser->setText(all);
    reply->deleteLater();
}


// 网络请求函数
void MainWindow::startRequest(QUrl url)
{
    reply = manager->get(QNetworkRequest(QUrl(url)));
    // 每当有新数据可以读取，都会发送  readySend() 信号，继承自QIODevice类
    connect(reply, SIGNAL(readySend()), this, SLOT(httpReadyRead()));
    // 每当网络请求的下载进度更新时，都会发送 downloadProgress 信号
    connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this,
        SLOT(updateDataReadProgress(qint64, qint64)));
    // 应答处理结束时，都会发送 finished() 信号
    connect(reply, SIGNAL(finished()), this, SLOT(httpFinished()));
}

void MainWindow::httpReadyRead()
{
    if (file) {	// 是否创建了文件，如果创建则读取返回的所有数据，然后写入文件中
        file->write(reply->readAll());
    }
}

void MainWindow::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesRead);
}

// 设置进度条的最大值和当前值
void MainWindow::httpFinished()
{
    // 完成下载后，隐藏进度条，删除 reply, file 对象
    ui->progressBar->hide();
    file->flush();
    file->close();
    reply->deleteLater();
    reply = nullptr;
    delete file;
    file = nullptr;
}



void MainWindow::on_pushButton_clicked()
{
    url = ui->lineEdit->text();
    QFileInfo info(url.path());
    QString fileName(info.fileName());
    file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly)) {
        qDebug() << "file open error";
        delete file;
        file = nullptr;
        return;
    }
    startRequest(url);
    ui->progressBar->setValue(0);
    ui->progressBar->show();
}
