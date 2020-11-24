#include "ThreadPool.h"

#include <QCoreApplication>
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QTimer>

qint64 getFileSize(const QString& url);
void multiDownload(const QString &url, qint64 fileSize, const QString &filename);

QMutex mutex;
int count = 0;

void sum(int a, int b)
{
    QMutexLocker lock(&mutex);
    count++;
    qDebug() << QString("%1+%2=%3").arg(a).arg(b).arg(a+b);
    qDebug() << QString("第%1次计算").arg(count);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ThreadPool pool;
    pool.start();
    qDebug() << "线程池启动完毕，当前任务队列有任务" << pool.tasksCount();
    for(size_t i = 0; i < 100; i++) {
        Task t(sum, i, i);
        pool.enqueue(t);
    }
    qDebug() << "任务添加完毕，当前任务队列有任务" << pool.tasksCount();
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&pool](){
        qDebug() << "当前任务队列有任务" << pool.tasksCount();
    });
    timer.setInterval(1000);
    timer.start();
//    QString url = "https://sample-videos.com/video123/mp4/720/big_buck_bunny_720p_10mb.mp4";
//    qint64 fileSize = getFileSize(url);
//    QString filename = QFileInfo(url).fileName();
//    multiDownload(url, fileSize, filename);
    return a.exec();
}


/**
 * @brief 获取要下载的文件大小
 * @param url
 */
qint64 getFileSize(const QString& url)
{

    QNetworkAccessManager requestManager;
    QEventLoop event;
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    QNetworkReply *reply = requestManager.head(request);
    QObject::connect(reply, &QNetworkReply::errorOccurred, [reply](QNetworkReply::NetworkError error){
        if (error != QNetworkReply::NoError) {
            qDebug() << reply->errorString();
        }
    });
    QObject::connect(reply, &QNetworkReply::finished, &event, &QEventLoop::quit);
    event.exec();
    qint64 fileSize = 0;
    if (reply->rawHeader("Accept-Ranges") == QByteArrayLiteral("bytes")
            && reply->hasRawHeader(QString("Content-Length").toLocal8Bit())) {
        fileSize = reply->header(QNetworkRequest::ContentLengthHeader).toUInt();
    }
    reply->deleteLater();
    return fileSize;
}


/**
 * @brief 多线程下载
 * @param url
 * @param fileSize
 * @param filename
 * @param threadCount
 */
void multiDownload(const QString &url, qint64 fileSize, const QString &filename)
{
    int threadCount = QThread::idealThreadCount();

    QFile file(filename);
    if (file.exists())
        file.remove();
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << file.errorString();
        return;
    }
    file.resize(fileSize);

    // 任务等分
    qint64 segmentSize = fileSize / threadCount;
    QVector<QPair<qint64, qint64>> vec(threadCount);
    for (int i = 0; i < threadCount; i++) {
        vec[i].first = i * segmentSize;
        vec[i].second = i * segmentSize + segmentSize - 1;
    }
    vec[threadCount-1].second = fileSize; // 余数部分加入最后一个

    qint64 bytesReceived = 0; // 下载接收的总字节数

    QMutex mutex;

    auto writeFile = [&](qint64 pos, QByteArray data){
        QMutexLocker lock(&mutex);
        qDebug() << QString("跳转文件位置%1，写入数据%2").arg(pos).arg(data.size());
        file.seek(pos);
        file.write(data);
        bytesReceived += data.size();
        if (fileSize == bytesReceived) {
            file.close();
            qDebug() << "下载完毕";
        }
    };

    // 任务队列
    auto downloadFunc = [writeFile, url](const QPair<qint64, qint64>& pair) {
        QNetworkAccessManager *mgr = new QNetworkAccessManager;
        QNetworkRequest request;
        request.setUrl(url);
        request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
        request.setRawHeader("Range", QString("bytes=%1-%2").arg(pair.first).arg(pair.second).toLocal8Bit());
        QNetworkReply *reply = mgr->get(request);
        qint64 writePos = pair.first;
        qint64 currentReceived = 0;
        qDebug() << "开始下载数据：" << QString(" %1~%2 ").arg(pair.first).arg(pair.second);
        QObject::connect(reply, &QNetworkReply::readyRead, [reply, writePos, writeFile, &currentReceived](){
            qDebug() << "测试，呜啦啦啦啦";
            qDebug() << "当前 currentReceived 的值为：" << currentReceived;
            qDebug() << QString("没有任何响应吗? writePos = %1, currentReceived=%2").arg(writePos).arg(currentReceived);
            QByteArray data = reply->readAll();
            writeFile(writePos + currentReceived, data);
            currentReceived += data.size();
        });
        QObject::connect(reply, &QNetworkReply::errorOccurred, [reply](QNetworkReply::NetworkError error){
            qDebug() << "发生了错误，呜啦啦啦" << reply->errorString();
        });
        QObject::connect(reply, &QNetworkReply::finished, mgr, &QNetworkAccessManager::deleteLater);
    };
    ThreadPool pool;
    pool.start();
    for (auto &pair : vec) {
        qDebug() << "输入任务数据，耶耶耶!";
        Task t(downloadFunc, pair);
        pool.enqueue(t);
    }
}
