#include "widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtNetwork/QNetworkRequest>
#include <QIcon>
#include <QFont>
#include <QTableWidgetItem>
#include <QBrush>
#include <QColor>
#include <QAbstractScrollArea>
#include <QUrlQuery>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    prevMobile = "";
    requestManager = new QNetworkAccessManager();

    setWindowTitle("学员手机号查询");
    setWindowFlags(Qt::WindowMinimizeButtonHint |
                   Qt::WindowCloseButtonHint |
                   Qt::WindowStaysOnTopHint);
    resize(300, 100);
    setWindowIcon(QIcon(":/app.ico"));


    auto hbox = new QHBoxLayout();
    mobileInput = new QLineEdit();
    mobileInput->setPlaceholderText("请输入手机号");
    realnameInput = new QLineEdit();
    realnameInput->setPlaceholderText("请输入姓名");
    queryBtn = new QPushButton();
    queryBtn->setIcon(QIcon(":/search.png"));
    hbox->addWidget(mobileInput);
    hbox->addWidget(realnameInput);
    hbox->addWidget(queryBtn);

    tableWidget = new QTableWidget();
    tableWidget->setColumnCount(4);
    tableWidget->setHorizontalHeaderLabels({ "姓名", "手机号", "班次", "注册时间" });
    QFont font = QFont("微软雅黑", 12);
    font.setBold(true);
    tableWidget->horizontalHeader()->setFont(font);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止编辑
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); // 整行选择
    tableWidget->resizeColumnsToContents();
    tableWidget->resizeRowsToContents();

    auto vbox = new QVBoxLayout();
    vbox->addLayout(hbox);
    vbox->addWidget(tableWidget);
    setLayout(vbox);

    connect(queryBtn, &QPushButton::released, this, &Widget::queryStudent);
    connect(mobileInput, &QLineEdit::returnPressed, this, &Widget::queryStudent);
    connect(realnameInput, &QLineEdit::returnPressed, this, &Widget::queryStudent);
}


/**
 * 像QTableWidget添加一行数据
 *
 * @brief Widget::center
 */
void Widget::addTableRow(QList<QString> &rowData)
{
    int row = tableWidget->rowCount();
    tableWidget->setRowCount(row + 1);
    int col = 0;
    for (auto &item : rowData) {
        auto cell = new QTableWidgetItem(item);
        cell->setBackground(QBrush(QColor(255, 160, 122)));
        tableWidget->setItem(row, col, cell);
        col++;
    }
    tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    tableWidget->resizeColumnsToContents();
    resize(sizeHint());
}

/**
 * 查询学员数据
 *
 * @brief Widget::center
 */
void Widget::queryStudent()
{
    if (!queryBtn->isEnabled()) {
        return;
    }

    QString mobile = mobileInput->text().trimmed();
    QString realname = realnameInput->text().trimmed();
    if (mobile.isEmpty() && realname.isEmpty()) {
        return showError("手机号和用户名不能同时为空");
    }

    tableWidget->setRowCount(0);

    QUrl url = QUrl(QString("http://www.anzhuoxfpx.com/extra_query.php"));
    auto request = QNetworkRequest(url);
    // request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencode");
    QByteArray data; 
    QUrlQuery params; 
    params.addQueryItem("action", "student_info"); 
    params.addQueryItem("mobile", mobile); 
    params.addQueryItem("realname", realname);
    data.append(params.toString().toUtf8());

    connect(requestManager, &QNetworkAccessManager::finished, this, &Widget::handleResponse);
    requestManager->post(request, data);
}

void Widget::handleResponse(QNetworkReply *reply)
{
    auto error = reply->error();
    if (error == QNetworkReply::NoError) {
        QByteArray buffer = reply->readAll();
        qDebug() << "响应数据为：" << buffer;
        if (buffer.isEmpty()) return;
        QJsonParseError jsonError;
        QJsonObject json = QJsonDocument::fromJson(buffer, &jsonError).object();
        if (jsonError.error != QJsonParseError::NoError) {
            return showError(QString("json解析错误：%1").arg(jsonError.errorString()));
        }
             
        if (json["code"].toInt() == 0) {
            queryBtn->setEnabled(true);
            QJsonArray data = json["data"].toArray();
            for (int i=0; i<data.count(); i++) {
                auto item = data.at(i);
                QList<QString> rowData = {
                    item["usertruename"].toString(),
                    item["username"].toString(),
                    item["groupname"].toString(),
                    item["regtime"].toString(),
                };
                addTableRow(rowData);
            }
        } else {
            return showError(json["msg"].toString() );
        }
    } else {
        return showError(reply->errorString());
    }
}

/**
 * 展示错误信息
 *
 * @brief Widget::center
 */
void Widget::showError(QString msg)
{
    queryBtn->setEnabled(true);
    auto msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("请求出错");
    msgBox->setIcon(QMessageBox::Critical);
    msgBox->setText(msg);
    msgBox->exec();
}

