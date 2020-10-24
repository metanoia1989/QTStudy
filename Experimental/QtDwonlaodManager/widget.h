#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


signals:
    void getFileSizeDone(QString url, qint64 filesize);

protected:
    void showError(QString msg);
    void getFileSize(QString url);
    void startDownload(QString url, qint64 fileSize = 0);


private slots:
    void on_downloadBtn_clicked();

    void on_brwoserPathBtn_clicked();

private:
    QNetworkAccessManager *requestManager;

    Ui::Widget *ui;
};
#endif // WIDGET_H
