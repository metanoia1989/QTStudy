#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    virtual ~Widget() {};
    void addTableRow(QList<QString> &rowData);
    void queryStudent();
    void showError(QString msg);

protected:
    void handleResponse(QNetworkReply *reply);

private:
    QString prevMobile;
    QLineEdit *textInput;
    QPushButton *queryBtn;
    QTableWidget *tableWidget;
    QNetworkAccessManager *requestManager;

signals:

};



#endif // WIDGET_H
