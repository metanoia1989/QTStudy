#ifndef CERTAPPROVAL_H
#define CERTAPPROVAL_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMetaType>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class CertApproval; }
QT_END_NAMESPACE

namespace AeaQt {
    class HttpClient;
};
class StudentItemModel;
class CheckboxHeader;
class ModifyMaterialDialog;
class QSimpleUpdater;

enum CertDataType {
    ClazzDataCert,
    LecturerDataCert,
    RecruiterDataCert,
    AssistantDataCert
};

Q_DECLARE_METATYPE(CertDataType)

class CertApproval : public QWidget
{
    Q_OBJECT

public:
    CertApproval(QWidget *parent = nullptr);
    ~CertApproval();

    void readSettings();
    void loadApprovalData();
    void initTableView();
    void updateUIStatus();
    void loadFilterData();
    void checkAppUpdate();

public slots:
    void showError(QString msg);
    void showApprovalData(QByteArray data);
    void showFilterData(CertDataType type, QStringList data);
    void ProvideContextMenu(const QPoint& position);
    void approvalProcessRequest(QString type = "approval");
    void approvalProcessBatch();

protected:
    void checkApprovalAuthority();

private slots:
    void on_refreshBtn_clicked();
    void on_nextPageBtn_clicked();
    void on_prePageBtn_clicked();

    void on_lineEdit_returnPressed();

    void on_searchBtn_clicked();

    void on_logoutBtn_clicked();

    void on_cb_pageSize_currentIndexChanged(const QString &arg1);

    void on_cbx_clazz_currentTextChanged(const QString &arg1);

    void on_resetFilterBtn_clicked();

    void makeApprovalMenu(QByteArray);

signals:
    void filterDataLoaded(CertDataType type, QStringList data);
    void requestShowError(QString msg);

private:
    QList<int> getSelectedIds();

    Ui::CertApproval *ui;
    StudentItemModel *model;
    AeaQt::HttpClient *httpClient;

    QString server_url; // 服务器地址
    QString keyword; // 搜索关键词
    QString clazz_name; // 班次名称
    int curr_page; // 当前页数
    int per_page; // 每页数量
    int last_page; // 最大页数
    bool loading; // 是否在加载

    QMenu *menu; // 右键菜单
    QMenu *batchMenu; // 批量处理菜单
    CheckboxHeader *header; // 自定义表格头部

    int selectedId = 0; // 被选择的学员ID
    int approval_status;

    QSimpleUpdater *m_updater;
};

#endif // CERTAPPROVAL_H
