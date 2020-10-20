#include <QCoreApplication>
#include <QtNetwork>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QNetworkAccessManager mgr;
    QUrl url = QUrl(QString("http://azxfsite.test/extra_query.php"));
    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-from-urlencoded"));
    auto data = QByteArray();
    data.append("action=student_info");
    data.append(QString("mobile=%1").arg("13593871052").toUtf8());

    auto *resp = mgr.post(req, data);
    //  mgr.post(req, data);

    QObject::connect(resp, &QNetworkReply::finished, [&]() {
        qDebug() << "FINISHED";
        if (resp->error() != QNetworkReply::NoError)
            qDebug() << "Error: " << resp->errorString();
        else
            qDebug() << "Status: " << resp->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
        
        QByteArray jsonArray = resp->readAll();
        qDebug() << QString::fromStdString(jsonArray.toStdString());
        // Stop when a response is received
        a.quit();
    });
    // QObject::connect(mgr, &QNetworkAccessManager::finished, [&](QNetworkReply *resp) {
    //     qDebug() << "FINISHED";
    //     QByteArray jsonArray = resp->readAll();
    //     qDebug() << QString::fromStdString(jsonArray.toStdString());
    //     // Stop when a response is received
    //     a.quit();
    // });
    printf("hello xmake\n");
    return a.exec();
}
