#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QCloseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "窗口关闭了\n";
    QMainWindow::closeEvent(event);
}
