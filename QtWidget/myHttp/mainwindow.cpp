#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this,
        SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("http://www.baidu.com")));

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
