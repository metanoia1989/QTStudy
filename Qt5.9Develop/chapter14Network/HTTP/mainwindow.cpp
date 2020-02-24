#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDir>
#include <QMessageBox>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->editURL->setClearButtonEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// 网络响应结束
void MainWindow::on_finished()
{
    QFileInfo fileInfo;
    fileInfo.setFile(downloadedFile->fileName());

    downloadedFile->close();
    delete downloadedFile;
    downloadedFile = nullptr;

    reply->deleteLater();
    reply = nullptr;

    if (ui->checkOpen->isChecked()) // 打开下载的文件
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));
    ui->btnDownload->setEnabled(true);
}

// 读取下载的数据
void MainWindow::on_readyRead()
{
    downloadedFile->write(reply->readAll());
}

// 下载进程
void MainWindow::on_downloadProgress(qint64 bytesRead, qint64 totalBytes)
{
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesRead);
}

// 缺省路径按钮
void MainWindow::on_btnDefaultPath_clicked()
{
    QString curPath = QDir::currentPath();
    QDir dir(curPath);

    QString sub = "temp";
    dir.mkdir(sub);

    QString path = QString("%1/%3/").arg(curPath).arg(sub);
    ui->editPath->setText(path);
}

// 开始下载按钮
void MainWindow::on_btnDownload_clicked()
{
    QString urlSpec = ui->editURL->text().trimmed();
    if (urlSpec.isEmpty())
    {
        QMessageBox::information(this, "错误", "请指定需要下载的URL");
        return;
    }
    QUrl newUrl = QUrl::fromUserInput(urlSpec);	// URL地址
    if (!newUrl.isValid())
    {
        QMessageBox::information(this, "错误",
             QString("无效URL：%1 \n 错误信息：%s").arg(urlSpec, newUrl.errorString()));
        return;
    }

    QString tempDir = ui->editPath->text().trimmed(); // 临时目录
    if (tempDir.isEmpty())
    {
        QMessageBox::information(this, tr("错误"), "请指定保存下载文件的目录");
        return;
    }

    QString fullFileName = tempDir + newUrl.fileName(); // 文件名
    if (QFile::exists(fullFileName))
        QFile::remove(fullFileName);

    downloadedFile = new QFile(fullFileName); // 创建临时文件
    if (!downloadedFile->open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("错误"), "临时文件打开错误");
        return;
    }

    ui->btnDownload->setEnabled(false);

    // 发送下载请求，创建网路响应
    reply = networkManager.get(QNetworkRequest(newUrl));
    connect(reply, &QNetworkReply::finished, this, &MainWindow::on_finished);
    connect(reply, &QNetworkReply::readyRead, this, &MainWindow::on_readyRead);
    connect(reply, &QNetworkReply::downloadProgress, this, &MainWindow::on_downloadProgress);
}

void MainWindow::on_editURL_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);
}
