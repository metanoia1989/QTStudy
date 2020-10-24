#include "widget.h"
#include "ui_widget.h"
#include "utils.h"
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>
#include <QFileDialog>
#include <QDir>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 设置URL链接验证器
    QRegExp regex(R"(http[s]://.+)");
    auto *validator = new QRegExpValidator(regex, nullptr);
    ui->urlInput->setValidator(validator);

    requestManager = new QNetworkAccessManager(this);
}

Widget::~Widget()
{
    delete ui;
}


/**
 * @brief 展示错误信息
 * @param msg
 */
void Widget::showError(QString msg)
{
    auto msgBox = new QMessageBox(this);
    msgBox->setWindowTitle(tr("请求出错"));
    msgBox->setIcon(QMessageBox::Critical);
    msgBox->setText(msg);
    msgBox->exec();
    ui->downloadBtn->setEnabled(true);
}



/**
 * @brief 获取要下载的文件大小
 * @param url
 */
void Widget::getFileSize(QString url)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QNetworkReply *reply = requestManager->head(request);
    connect(reply, &QNetworkReply::finished, [reply, url, this](){
        qint64 fileSize = 0;
        if (reply->hasRawHeader(QString("Content-Length").toLocal8Bit())) {
            fileSize = reply->header(QNetworkRequest::ContentLengthHeader).toUInt();
        }
        emit getFileSizeDone(url, fileSize);
        reply->deleteLater();
    });
    connect(reply, &QNetworkReply::errorOccurred, [this, reply](QNetworkReply::NetworkError error){
        if (error != QNetworkReply::NoError) {
            return showError(reply->errorString());
        }
    });
}


/**
 * @brief 开始下载文件
 * @param url
 * @param fileSize 值为0时下载整个文件，值不为0时断点传续或者多线程下载
 */
void Widget::startDownload(QString url, qint64 fileSize)
{
    // 显示要下载的文件大小
    QString sizeText = fileSize == 0 ? "未知大小" : Utils::sizeFormat(fileSize);
    ui->filesizeLabel->setText(sizeText);

    // 本地创建文件
    QFileInfo info(QUrl(url).path());
    QString fileName(info.fileName());
    if (fileName.isEmpty()) {
        return showError("无效的文件名");
    }
    QString savePath = ui->savePathInput->text().trimmed();
    if (savePath.isEmpty() || !QDir(savePath).exists()) {
        return showError("无效的保存路径");
    }
    QDir::setCurrent(savePath);
    QFile *file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly)) {
        delete file;
        file = nullptr;
        return ;
    }

    // 发起文件下载请求
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QNetworkReply *reply = requestManager->get(request);
    connect(reply, &QNetworkReply::errorOccurred, [this, reply](QNetworkReply::NetworkError error){
        if (error != QNetworkReply::NoError) {
            return showError(reply->errorString());
        }
    });
    connect(reply, &QNetworkReply::finished, [reply, file, this](){
        file->flush();
        file->close();
        delete file;
        reply->deleteLater();
        ui->downloadBtn->setEnabled(true);
    });
    connect(reply, &QNetworkReply::readyRead, [reply, file](){
        file->write(reply->readAll());
    });

    connect(reply, &QNetworkReply::downloadProgress, [this](qint64 bytesReceived, qint64 bytesTotal){
        if (bytesTotal <= 0) return;
        ui->downProgressBar->setMaximum(10000); // 最大值
        ui->downProgressBar->setValue((bytesReceived * 10000) / bytesTotal); // 当前值
        ui->downProgressBar->setTextVisible(true);
    });
}

/**
 * @brief  点击开始下载
 */
void Widget::on_downloadBtn_clicked()
{
    QString url = ui->urlInput->text().trimmed();
    if (url.isEmpty()) {
        return showError(tr("请求链接不允许为空！"));
    }

    // 选择保存路径
    QString savePath = ui->savePathInput->text().trimmed();
    if (savePath.isEmpty()) {
        savePath = QFileDialog::getExistingDirectory();
        if (savePath.isEmpty()) return;
    } else {
        if(!QDir(savePath).exists()) {
            return showError(tr("路径不存在！"));
        }
    }

    ui->downloadBtn->setEnabled(false);
    getFileSize(url);

    connect(this, &Widget::getFileSizeDone, this, &Widget::startDownload);
}

/**
 * @brief 设置保存下载文件的路径
 */
void Widget::on_brwoserPathBtn_clicked()
{
    QString savePath = QFileDialog::getExistingDirectory();
    if (!savePath.isEmpty()) {
        ui->savePathInput->setText(savePath);
    }
}
