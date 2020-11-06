#if !defined(DownloadManager_H)
#define DownloadManager_H

#include <QtCore>
#include <QtNetwork>
#include <cstdio>


QT_BEGIN_NAMESPACE
class QSslError;
QT_END_NAMESPACE

class DownloadManager : public QObject
{
    Q_OBJECT
public:
    DownloadManager();
    void doDownload(const QUrl &url);
    static QString saveFileName(const QUrl &url);
    bool saveToDisk(const QString &filename, QIODevice *data);
    static bool isHttpRedirect(QNetworkReply *reply);

public slots:
    void execute();
    void downloadFinished(QNetworkReply *reply);
    void sslErrors(const QList<QSslError> &errors);

private:
    QNetworkAccessManager manager;
    QVector<QNetworkReply *> currentDownloads;
};

#endif // DownloadManager_H
