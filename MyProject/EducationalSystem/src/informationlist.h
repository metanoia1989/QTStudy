#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMetaType>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class InformationList; }
QT_END_NAMESPACE

namespace AeaQt {
    class HttpClient;
};
class StudentItemModel;
class CheckboxHeader;
class ModifyMaterialDialog;
class QSimpleUpdater;

enum DataType {
    ClazzData,
    LecturerData,
    RecruiterData
};

Q_DECLARE_METATYPE(DataType)

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
    void loadFilterData();
    void checkAppUpdate();

public slots:
    void showError(QString msg);
    void showStudentData(QByteArray data);
    void showFilterData(DataType type, QStringList data);
    void cellDataChange(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    void ProvideContextMenu(const QPoint& position);
    void materialProcessRequest(QString type);
    void materialProcessBatch(QString type);

private slots:
    void on_refreshBtn_clicked();
    void on_nextPageBtn_clicked();
    void on_prePageBtn_clicked();

    void on_lineEdit_returnPressed();

    void on_searchBtn_clicked();

    void on_logoutBtn_clicked();

    void on_cb_pageSize_currentIndexChanged(const QString &arg1);

    void on_cbx_clazz_currentTextChanged(const QString &arg1);

    void on_cbx_recruiter_currentTextChanged(const QString &arg1);

    void on_cbx_lecturer_currentTextChanged(const QString &arg1);

    void on_resetFilterBtn_clicked();

signals:
    void filterDataLoaded(DataType type, QStringList data);
    void requestShowError(QString msg);

private:
    QList<int> getSelectedIds();

    Ui::InformationList *ui;
    StudentItemModel *model;
    AeaQt::HttpClient *httpClient;

    QString server_url; // 服务器地址
    QString keyword; // 搜索关键词
    QString clazz_name; // 班次名称
    QString recruiter_name; // 招生老师
    QString lecturer_name; // 授课老师
    int curr_page; // 当前页数
    int per_page; // 每页数量
    int last_page; // 最大页数
    bool loading; // 是否在加载

    QMenu *menu; // 右键菜单
    QMenu *batchMenu; // 批量处理菜单
    CheckboxHeader *header; // 自定义表格头部

    QString remark = ""; // 资料收齐备注
    int selectedId = 0; // 被选择的学员ID
    QString selectedValue = 0; // 选择项的值

    QMap<QString, int> materialFields; // 批量更新资料字段的结果值
    QSimpleUpdater *m_updater;
};

#endif // MAINWINDOW_H
