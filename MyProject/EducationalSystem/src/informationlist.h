#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class InformationList; }
QT_END_NAMESPACE

namespace AeaQt {
    class HttpClient;
};
class StudentItemModel;

class InformationList : public QWidget
{
    Q_OBJECT

public:
    InformationList(QWidget *parent = nullptr);
    ~InformationList();

    void readSettings();
    void loadStudentData();
    void initTableView();
    void updateUIStatus();

public slots:
    void showError(QString msg);
    void showStudentData(QByteArray data);
    void cellDataChange(const QModelIndex &topLeft, const QModelIndex &bottomRight);

private slots:
    void on_refreshBtn_clicked();
    void on_nextPageBtn_clicked();
    void on_prePageBtn_clicked();

    void on_lineEdit_returnPressed();

    void on_searchBtn_clicked();

    void on_refreshBtn_2_clicked();

    void on_cb_pageSize_currentIndexChanged(const QString &arg1);

private:
    Ui::InformationList *ui;

    StudentItemModel *model;

    AeaQt::HttpClient *httpClient;
    QString server_url; // 服务器地址
    QString keyword; // 搜索关键词
    int curr_page; // 当前页数
    int per_page; // 每页数量
    int last_page; // 最大页数
    bool loading; // 是否在加载
};
#endif // MAINWINDOW_H