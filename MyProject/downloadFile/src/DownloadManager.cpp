#include "DownloadManager.h"

DownloadManager::DownloadManager() 
{
    connect(&manager, &QNetworkAccessManager::finished,
            this, &DownloadManager::downloadFinished);
}

void DownloadManager::doDownload(const QUrl &url) 
{
    QNetworkRequest request(url);
    QNetworkReply *reply = manager.get(request);
#if QT_CONFIG(ssl)
    connect(reply, &QNetworkReply::sslErrors,
            this, &DownloadManager::sslErrors);
#endif
    currentDownloads.append(reply);
}

/**
 * 要保存的文件名
 */
QString DownloadManager::saveFileName(const QUrl &url) 
{
    QString path = url.path();
    QString basename = QFileInfo(path).fileName();

    if (basename.isEmpty())
        basename = "download";
    if (QFile::exists(basename)) {
        int i = 0;
        basename += '.';
        while (QFile::exists(basename + QString::number(i)))
            ++i;
        basename += QString::number(i);
    }
    return basename;
}

bool DownloadManager::saveToDisk(const QString &filename, QIODevice *data) 
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        fprintf(stderr, "Could not open %s for writing: %s\n",
                qPrintable(filename), qPrintable(file.errorString()));
        return false;
    }
    file.write(data->readAll());
    file.close();
}

bool DownloadManager::isHttpRedirect(QNetworkReply *reply) 
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QList<int> codes = { 301, 302, 303, 305, 307, 308 };
    return codes.contains(statusCode);
}

void DownloadManager::execute() 
{
    printf("测试输出");
    QStringList args = QCoreApplication::instance()->arguments();
    args.takeFirst();
    if (args.isEmpty()) {
        printf("Qt Download Example - 必须要传递参数过来！");
        return QCoreApplication::instance()->quit();
    }

    for (const QString &arg : qAsConst(args)) {
        QUrl url = QUrl::fromEncoded(arg.toLocal8Bit());
        doDownload(url);
    }
}

void DownloadManager::downloadFinished(QNetworkReply *reply) 
{
    QUrl url = reply->url();
    if (reply->error()) {
        fprintf(stderr, "Download of %s failed: %s\n",
                url.toEncoded().constData(),
                qPrintable(reply->errorString()));
    } else {
        if (isHttpRedirect(reply)) {
            fputs("Request was redirected.\n", stderr);
        } else {
            QString filename = saveFileName(url);
            if (saveToDisk(filename, reply)) {
                printf("Download of %s success (saved to %s)\n",
                      url.toEncoded().constData(), qPrintable(filename));
            }
        }
    }
    currentDownloads.removeAll(reply);
    reply->deleteLater();

    if (currentDownloads.isEmpty()) {
        QCoreApplication::instance()->quit();
    }
}


void DownloadManager::sslErrors(const QList<QSslError> &errors)
{
#if QT_CONFIG(ssl)
    for (const QSslError &error : errors)
        fprintf(stderr, "SSL error: %s\n", qPrintable(error.errorString()));
#else
    Q_UNUSED(errors);
#endif
}
