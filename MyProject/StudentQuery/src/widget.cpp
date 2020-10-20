#include "widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
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


    auto hbox = new QHBoxLayout();
    textInput = new QLineEdit();
    queryBtn = new QPushButton();
    queryBtn->setIcon(QIcon(":/app.ico"));
    hbox->addWidget(textInput);
    hbox->addWidget(queryBtn);

    tableWidget = new QTableWidget();
    tableWidget->setColumnCount(4);
    tableWidget->setHorizontalHeaderLabels({ "姓名", "手机号", "班次", "注册事件" });
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
    connect(textInput, &QLineEdit::returnPressed, this, &Widget::queryStudent);
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

    QString mobile = textInput->text().trimmed();
    if (mobile.isEmpty()) {
        return showError("手机号不能为空");
    }
    if (prevMobile == mobile) {
        return showError("手机号没有变动");
    }
    prevMobile = mobile;

    tableWidget->setRowCount(0);

    QUrl url = QUrl(QString("http://azxfsite.test/extra_query.php"));
    auto request = QNetworkRequest(url);
    // request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencode");
    QByteArray data; 
    QUrlQuery params; 
    params.addQueryItem("action", "student_info"); 
    params.addQueryItem("mobile", mobile); 
    data.append(params.toString());

    connect(requestManager, &QNetworkAccessManager::finished, this, &Widget::handleResponse);
    requestManager->post(request, data);
}

void Widget::handleResponse(QNetworkReply *reply)
{
    qDebug() << "响应信息" << QString::fromStdString(reply->readAll().toStdString()); 
    auto error = reply->error();
    if (error == QNetworkReply::NoError) {
        QByteArray buffer = reply->readAll();
        QJsonObject json = QJsonDocument::fromJson(buffer.toUtf8()).object();
        qDebug() << json;
             
        if (json["code"].toInt() == 0) {
            queryBtn->setEnabled(true);
            QJsonObject data = json["data"].toObject();
            QList<QString> rowData = {
                data["usertruename"].toString(),
                data["username"].toString(),
                data["groupname"].toString(),
                data["regtime"].toString(),
            };
            addTableRow(rowData);
        } else {
            showError(json["msg"].toString() );
        }
    } else {
        showError(reply->errorString());
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

