#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include <QTextDocument>
#include <QTextBlock>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->tabWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 用IODevice方式打开文本文件
bool MainWindow::openTextByIODevice(const QString &aFileName)
{
    QFile aFile(aFileName);

    if (!aFile.exists()) {
        return false;
    }
    if (!aFile.open(QIODevice::ReadOnly|QIODevice::Text)) {
        return false;
    }

    ui->textEditDevice->setPlainText(aFile.readAll());
    aFile.close();

    ui->tabWidget->setCurrentIndex(0);

    return true;
}

// 用IODevice方式保存文本文件
bool MainWindow::saveTextByIODevice(const QString &aFileName)
{
    QFile aFile(aFileName);
    if (!aFile.open(QIODevice::WriteOnly|QIODevice::Text)) {
        return false;
    }

    QString str = ui->textEditDevice->toPlainText();
    QByteArray strBytes = str.toUtf8(); // 字符串转换为字节数组

    aFile.write(strBytes, strBytes.length());	// 写入文件
    aFile.close();

    ui->tabWidget->setCurrentIndex(0);

    return true;
}

// 用QTextStream打开文本文件
bool MainWindow::openTextByStream(const QString &aFileName)
{
    QFile aFile(aFileName);

    if (!aFile.exists()) {
        return false;
    }
    if (!aFile.open(QIODevice::ReadOnly|QIODevice::Text)) {
        return false;
    }

    QTextStream aStream(&aFile); // 用文本流读取文件
    ui->textEditStream->setPlainText(aStream.readAll());

    aFile.close();

    ui->tabWidget->setCurrentIndex(1);

    return true;
}

// 用QTextStream保存文本文件
bool MainWindow::saveTextByStream(const QString &aFileName)
{
    QFile aFile(aFileName);
    if (!aFile.open(QIODevice::WriteOnly|QIODevice::Text)) {
        return false;
    }

    QTextStream aStream(&aFile);
    QString str = ui->textEditStream->toPlainText();
    aStream >> str;
    aFile.close();

    return true;
}

void MainWindow::on_actOpen_IODevice_triggered()
{
    QString curPath = QDir::currentPath(); // 获取系统当前目录
    QString dlgTitle = "打开一个文件"; // 对话框标题
    QString filter = "程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)";
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);

    if (aFileName.isEmpty()) {
        return;
    }

    openTextByIODevice(aFileName);
}

void MainWindow::on_actSave_IODevice_triggered()
{
    QString curPath = QDir::currentPath(); // 获取系统当前目录
    QString dlgTitle = "另存为一个文件"; // 对话框标题
    QString filter = "程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)";
    QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);

    if (aFileName.isEmpty()) {
        return;
    }

    saveTextByIODevice(aFileName);
}

void MainWindow::on_actOpen_TextStream_triggered()
{
    QString curPath = QDir::currentPath(); // 获取系统当前目录
    QString dlgTitle = "打开一个文件"; // 对话框标题
    QString filter = "程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)";
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);

    if (aFileName.isEmpty()) {
        return;
    }

    openTextByStream(aFileName);
}

void MainWindow::on_actSave_TextStream_triggered()
{
    QString curPath = QDir::currentPath(); // 获取系统当前目录
    QString dlgTitle = "另存为一个文件"; // 对话框标题
    QString filter = "程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)";
    QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);

    if (aFileName.isEmpty()) {
        return;
    }

    saveTextByStream(aFileName);
}
