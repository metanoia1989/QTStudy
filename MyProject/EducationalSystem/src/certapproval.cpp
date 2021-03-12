#include "certapproval.h"
#include "ui_certapproval.h"
#include "studentitemmodel.h"
#include "checkboxheader.h"
#include "delegate/certificatedelegate.h"
#include "delegate/collectiondelegate.h"
#include "delegate/datedelegate.h"
#include "delegate/paperphotodelegate.h"
#include "delegate/techmaterialdelegate.h"
#include "approvaldialog.h"

#include "utils/global.h"
#include "utils/cache.h"
#include "utils/threads.h"
#include "HttpClient.h"
#include <QSimpleUpdater.h>

#include <QMessageBox>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTimer>
#include <QProcess>
#include <QMenu>
#include <QAction>
#include <QPoint>
#include <QStyle>
#include <QInputDialog>
#include <QList>
#include <QClipboard>
#include <QCompleter>

CertApproval::CertApproval(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CertApproval)
    , curr_page(1)
    , per_page(100)
    , last_page(100)
    , loading(false)
{
    ui->setupUi(this);

     httpClient = new AeaQt::HttpClient;

     // 读取服务器地址
     readSettings();

     initTableView(); // =_= 这里面有网络请求操作，我给忘了，之前竟然放到了前面

     QTimer::singleShot(0, this, &CertApproval::loadApprovalData);
     loadFilterData();
}

CertApproval::~CertApproval()
{
    delete ui;
    delete httpClient;
}

/**
 * @brief CertApproval::initTableView
 */
void CertApproval::initTableView()
{

    model = new StudentItemModel(this);
    model->setColumnCount(9);
    model->setDisableColumns({
        0, 1, 2, 3,
        4, 5, 6, 7,
        8
    });
    model->setHorizontalHeaderLabels({
        "     ID",
        "学员姓名", "班次", "申请人", "审批类型",
        "更新的数据", "审批状态", "备注", "创建时间",
    });

    ui->studentsDataTable->setModel(model);
    ui->studentsDataTable->setAlternatingRowColors(true);
    ui->studentsDataTable->setStyleSheet("QTableView{background-color: #fff;"
    "alternate-background-color: #f3f3f3;}");
    ui->studentsDataTable->verticalHeader()->hide();


    QFont font = QFont("微软雅黑", 12);
    font.setBold(true);
    ui->studentsDataTable->horizontalHeader()->setFont(font);

    // 设置 header
    header = new CheckboxHeader(Qt::Horizontal, ui->studentsDataTable);
    ui->studentsDataTable->setHorizontalHeader(header);
    connect(header, &CheckboxHeader::selectAllClicked, [this](QStyle::StateFlag state){
        for (int i = 0; i < model->rowCount(); i++) {
            auto item = model->item(i, 0);
            if (state == QStyle::State_On) {
                item->setCheckState(Qt::Checked);
            } else {
                item->setCheckState(Qt::Unchecked);
            }
        }
    });

    // 检测是否有审批权限
    checkApprovalAuthority();
}

/**
 * 更新UI显示情况
 *
 * @brief CertApproval::updateUIStatus
 */
void CertApproval::updateUIStatus()
{
    if (per_page <= 1) {
        ui->prePageBtn->setDisabled(true);
    } else if (per_page == last_page) {
        ui->nextPageBtn->setDisabled(true);
    } else {
        ui->prePageBtn->setDisabled(false);
        ui->nextPageBtn->setDisabled(false);
    }
    ui->currentPageLabel->setText(QString("第%1页").arg(curr_page));
    ui->sumPageLabel->setText(QString("共%1页").arg(last_page));
    ui->cb_pageSize->setCurrentText(QString::number(per_page));
}

/**
 * @brief 加载筛选数据
 */
void CertApproval::loadFilterData()
{

    class GetTokenRunnable : public QObject
    {
        CertApproval * m_p;
        QString m_token;
    public:
        GetTokenRunnable(CertApproval * p, QString token)
            : m_p(p), m_token(token)
        {
        }

        void run(CertDataType type)
        {

            QString filter_data_url = getServerUrl() + "/api/desktop/%1";
            if (type == CertDataType::ClazzDataCert) {
                filter_data_url = filter_data_url.arg("clazz");
            } else if (type == CertDataType::AssistantDataCert) {
                filter_data_url = filter_data_url.arg("assistant");
            } else {
                emit m_p->requestShowError("无效的筛选类型");
                return;
            }

            AeaQt::HttpClient httpClient;
            auto response =  httpClient.get(filter_data_url)
                .header("content-type", "application/json")
                .header("authorization", QString("Bearer %1").arg(m_token))
                .timeout(10 * 1000) // 10s超时
                .block()
                .exec();
            qDebug() << "发起请求：" << filter_data_url;
            qDebug() << "请求token为：" <<  m_token;
            QNetworkReply *reply = response->networkReply();
            if (reply->error() == QNetworkReply::NoError) {
                QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
                qDebug() << "请求成功：" << json;
                if (json["code"].toInt() != 0) {
                    qDebug() << "发生错误：" << json["msg"].toString();
                    emit m_p->requestShowError(json["msg"].toString());
                    return;
                }
                QStringList strList;
                auto data = json["data"].toArray();
                for (int i = 0; i < data.count(); i++) {
                    strList << data.at(i).toString();
                }
                emit m_p->filterDataLoaded(type, strList);
            } else {
                qDebug() << "发生错误：" << reply->errorString();
                emit m_p->requestShowError(reply->errorString());
            }
        }
    };
    QString token = Global::cache()->getItem("token");
    ExecuteOnThread(THREAD_DOWNLOAD, [=](){
        GetTokenRunnable runnable(this, token);
        runnable.run(CertDataType::ClazzDataCert);
    });
    ExecuteOnThread(THREAD_NETWORK, [=](){
        GetTokenRunnable runnable(this, token);
        runnable.run(CertDataType::AssistantDataCert);
    });
    connect(this, &CertApproval::filterDataLoaded, this, &CertApproval::showFilterData, Qt::QueuedConnection);
    connect(this, &CertApproval::requestShowError, this, &CertApproval::showError, Qt::QueuedConnection);
}

/**
 * @brief 获取选中的学员ID
 * @return QList<int>
 */
QList<int> CertApproval::getSelectedIds()
{
    QList<int> ids;
    for (int i = 0; i < model->rowCount(); i++) {
        auto item = model->item(i, 0);
        if (item->checkState() == Qt::Checked) {
            int studentId = item->data(Qt::UserRole + 1).value<int>();
            ids.push_back(studentId);
        }
    }
    return ids;
}

/**
 * @brief 展示被加载的数据
 * @param type
 * @param data
 */
void CertApproval::showFilterData(CertDataType type, QStringList data)
{
    if (type == CertDataType::ClazzDataCert) {
        ui->cbx_clazz->clear();
        ui->cbx_clazz->addItem("选择班次");
        ui->cbx_clazz->addItems(data);
    } else if (type == CertDataType::AssistantDataCert) {
        ui->cbx_proposer->clear();
        ui->cbx_proposer->addItem("选择申请人");
        ui->cbx_proposer->addItems(data);
    }
}

/**
 * 读取配置
 *
 * @brief CertApproval::readSettings
 */
void CertApproval::readSettings()
{
    server_url = getServerUrl();
    if (server_url.isEmpty()) {
        showError(tr("读取教务系统地址失败，请检查配置文件！"));
    }
}

/**
 * 展示错误信息
 *
 * @brief CertApproval::showError
 * @param msg
 */
void CertApproval::showError(QString msg)
{
    auto msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("请求出错");
    msgBox->setIcon(QMessageBox::Critical);
    msgBox->setText(msg);
    msgBox->exec();
    loading = false;
}


/**
 * 加载学员数据
 *
 * @brief CertApproval::loadApprovalData
 */
void CertApproval::loadApprovalData()
{
    loading = true;
    QString student_list_url = server_url + "/api/desktop/approval/list";
    QString token = Global::cache()->getItem("token");
    httpClient->get(student_list_url)
        .header("content-type", "application/json")
        .header("authorization", QString("Bearer %1").arg(token))
        .queryParam("page_size",per_page)
        .queryParam("page_num", curr_page)
        .queryParam("keyword", QUrl::toPercentEncoding(keyword))
        .queryParam("clazz_name", clazz_name)
        .onResponse(this, SLOT(showApprovalData(QByteArray)))
        .onError(this, SLOT(showError(QString)))
        .timeout(10 * 1000) // 10s超时
        .exec();
}

void CertApproval::showApprovalData(QByteArray result)
{
    QJsonObject json = QJsonDocument::fromJson(result).object();
    if (json.isEmpty()) {
        return showError("服务器响应为空！");
    }
    if (json["code"].toInt() != 0) {
        return showError(json["msg"].toString());
    }
    QJsonObject data = json["data"].toObject();
    curr_page = data["current_page"].toInt();
    last_page = data["last_page"].toInt();
    QJsonArray studentList = data["data"].toArray();

    model->setRowCount(0);

    for (int i=0; i<studentList.count(); i++) {
        auto studentItem = studentList.at(i).toObject();

        QList<QString> keys = {
            "id", "student_name", "clazz_name", "proposer_name",
            "approval_type", "extra_data_text", "approval_status",
            "remark", "created_at"
        };

        QList<QStandardItem*> rowData;
        for(auto &key: keys) {
            QStandardItem *item = new QStandardItem;
            // 设置显示的内容
            if (key == "approval_status") { // 标志整个审批状态
                if (studentItem[key].toInt() == 1) {
                    item->setData("通过", Qt::DisplayRole);
                    item->setData(QIcon(":/icons/tick.png"), Qt::DecorationRole);
                } else if (studentItem[key].toInt() == 2) {
                    item->setData("驳回", Qt::DisplayRole);
                    item->setData(QIcon(":/icons/cross.png"), Qt::DecorationRole);
                } else {
                    item->setData("未审批", Qt::DisplayRole);
                    item->setData(QIcon(":/icons/wait.png"), Qt::DecorationRole);
                }
            } else if (key == "id") {
                item->setData(studentItem[key].toInt(), Qt::DisplayRole);
                item->setCheckable(true);
            } else {
                QString text = studentItem[key].toString();
                if (text == "未收齐") text = "";
                item->setData(text, Qt::DisplayRole);
            }
            // 设置自定义数据项
            item->setData(studentItem["id"].toInt(), Qt::UserRole + 1); // 学员ID
            item->setData(key, Qt::UserRole + 2); // 字段名称
            item->setData(studentItem[key].toString(), Qt::UserRole + 3); // 原始值
            rowData.append(item);
        }

        model->appendRow(rowData);
    }
    ui->studentsDataTable->resizeColumnsToContents();
    ui->studentsDataTable->resizeRowsToContents();
    loading = false;
    updateUIStatus();
}


/**
 * @brief 提供右键菜单
 * @param position
 */
void CertApproval::ProvideContextMenu(const QPoint& position)
{
    qDebug() << "测试是否被调用" << position.x() << "," << position.y();
    int row = ui->studentsDataTable->rowAt(position.y());
    int cellHeight = ui->studentsDataTable->rowHeight(row);
    QStandardItem *item = model->itemFromIndex(ui->studentsDataTable->indexAt(position));
    selectedId = item->data(Qt::UserRole + 1).value<int>();

    qDebug() << "此条记录的学员ID: " << selectedId;

    auto pos = ui->studentsDataTable->mapToGlobal(position);
    menu->exec(pos + QPoint(0, cellHeight * 1.5));
}

/**
 * @brief 资料收齐申请相关处理
 * @param type
 */
void CertApproval::approvalProcessRequest(QString type)
{
    if (loading) return;

    if (selectedId == 0) {
        return showError("无效的学员ID！");
    }

    qDebug() << "type的类型为：" << type;
    loading = true;
    QString url = server_url + "/api/desktop/approval/batUpdate";
    if (type.compare("restore") == 0) {
        url = server_url + "/api/desktop/approval/restore";
    } else {
        qDebug() << "type is restore ? " << type.compare("restore") << " " << (type.compare("restore") == 0);
    }
    QString token = Global::cache()->getItem("token");
    qDebug() << "发起请求：" << url.arg(selectedId);
    QVariantMap data;
    data.insert("id", selectedId);
    data.insert("approval_status", approval_status);
    httpClient->post(url)
        .header("content-type", "application/json")
        .header("authorization", QString("Bearer %1").arg(token))
        .body(data)
        .onResponse([this](QByteArray result){
            loading = false;
            selectedId = 0;
            QJsonObject json = QJsonDocument::fromJson(result).object();
            if (json.isEmpty()) {
                return showError("服务器响应为空！");
            }
            if (json["code"].toInt() != 0) {
                return showError(json["msg"].toString());
            }
            loadApprovalData();
            return showSuccessMsg(json["msg"].toString());
        })
        .onError([this](QString errorStr){
            loading = false;
            selectedId = 0;
            showError(errorStr);
        })
        .timeout(10 * 1000) // 10s超时
            .exec();
}

/**
 * @brief 批处理资料申请
 * @param type
 */
void CertApproval::approvalProcessBatch()
{
    if (loading) return;

    QList<int> studentIds = getSelectedIds();
    if (studentIds.empty()) {
        return showError("没有选中任何记录！");
    }
    QStringList id_list;
    for(int i = 0; i < studentIds.count(); i++) {
        id_list << QString::number(studentIds.at(i));
    }
    QString ids = id_list.join(",");

    loading = true;
    QString url = server_url + "/api/desktop/approval/batUpdate";
    QString token = Global::cache()->getItem("token");
    qDebug() << "发起请求：" << url;
    QVariantMap data;
    data.insert("id", ids);
    data.insert("approval_status", approval_status);

    httpClient->post(url)
        .header("content-type", "application/json")
        .header("authorization", QString("Bearer %1").arg(token))
        .body(data)
        .onResponse([this](QByteArray result){
            loading = false;
            QJsonObject json = QJsonDocument::fromJson(result).object();
            if (json.isEmpty()) {
                return showError("服务器响应为空！");
            }
            if (json["code"].toInt() != 0) {
                return showError(json["msg"].toString());
            }
            loadApprovalData();
            return showSuccessMsg(json["msg"].toString());
        })
        .onError([this](QString errorStr){
            loading = false;
            showError(errorStr);
        })
        .timeout(10 * 1000) // 10s超时
            .exec();
}

/**
 * @brief 检测结业证审批权限
 */
void CertApproval::checkApprovalAuthority()
{
    loading = true;
    QString url = server_url + "/api/desktop/approval/authority";
    QString token = Global::cache()->getItem("token");

    httpClient->get(url)
        .header("content-type", "application/json")
        .header("authorization", QString("Bearer %1").arg(token))
        .onResponse(this, SLOT(makeApprovalMenu(QByteArray)))
        .onError([this](QString errorStr){
            loading = false;
            showError(errorStr);
        })
        .timeout(10 * 1000) // 10s超时
            .exec();
}

void CertApproval::makeApprovalMenu(QByteArray result)
{
    loading = false;
    QJsonObject json = QJsonDocument::fromJson(result).object();
    if (json.isEmpty()) {
        return showError("服务器响应为空！");
    }
    if (json["code"].toInt() != 0) {
        return showError(json["msg"].toString());
    }

    qDebug() << "获取权限成功！！！" << result;

    QJsonObject data = json["data"].toObject();
    bool edit = data["edit"].toBool();

    if (!edit) {
        return;
    }
    // 设置右键菜单
    menu = new QMenu(ui->studentsDataTable);
    QAction *approvalAction = new QAction("审批");
    QAction *restoreAction = new QAction("撤销");
    menu->addActions({ approvalAction, restoreAction });

    ui->studentsDataTable->setContextMenuPolicy(Qt::CustomContextMenu);

    ApprovalDialog *approvalDialog = new ApprovalDialog(this);

    connect(approvalAction, &QAction::triggered, [this, approvalDialog](){
        // 审批处理
        approvalDialog->clearChecked();
        if (approvalDialog->exec()) {
            approval_status = approvalDialog->getResult();
            if (approval_status != -1) {
                approvalProcessRequest();
            }
        }
    });
    connect(restoreAction, &QAction::triggered, [this](){
        int result = QMessageBox::information(this, "确认提示", "确认要撤销审批操作吗？", tr("确认"), tr("取消"));
        if (result == tr("确定").toInt()) {
            approvalProcessRequest("restore");
        }
    });
    connect(ui->studentsDataTable, &QTableView::customContextMenuRequested,
                this, &CertApproval::ProvideContextMenu);

    // 设置批处理的右键菜单
    batchMenu = new QMenu(this);
    QAction *approvalBatAct = new QAction("批量审批");

    batchMenu->addActions({ approvalBatAct });
    ui->batchBtn->setMenu(batchMenu);
    connect(approvalBatAct, &QAction::triggered, [this, approvalDialog](){
        // 批量审批处理
        approvalDialog->clearChecked();
        if (approvalDialog->exec()) {
            approval_status = approvalDialog->getResult();
            if (approval_status != -1) {
                approvalProcessBatch();
            }
        }
    });
}


void CertApproval::on_refreshBtn_clicked()
{
    if (loading)  return;
    loadApprovalData();
}

void CertApproval::on_nextPageBtn_clicked()
{
    if (loading || curr_page == last_page)  return;
    curr_page++;
    updateUIStatus();
    loadApprovalData();
}

void CertApproval::on_prePageBtn_clicked()
{
    if (loading || curr_page <= 1)  return;
    curr_page--;
    loadApprovalData();
}

/**
 * 用户按下回车键
 * @brief CertApproval::on_lineEdit_returnPressed
 */
void CertApproval::on_lineEdit_returnPressed()
{
    if (loading) return;
    loading = true;
    keyword = ui->lineEdit->text().trimmed();
    loadApprovalData();
}

/**
 * 点击搜索框
 * @brief CertApproval::on_searchBtn_clicked
 */
void CertApproval::on_searchBtn_clicked()
{
    if (loading) return;
    loading = true;
    keyword = ui->lineEdit->text().trimmed();
    loadApprovalData();
}

/**
 * @brief 点击注销按钮
 */
void CertApproval::on_logoutBtn_clicked()
{
    Global::cache()->setItem("autoLogin", "0");
    Global::cache()->setItem("token", "");
    qApp->closeAllWindows();
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
}

void CertApproval::on_cb_pageSize_currentIndexChanged(const QString &arg1)
{
    int num = arg1.toInt();
    if (num == per_page || loading) {
        return;
    }
    per_page = num;
    curr_page = 1;
    loadApprovalData();
}

void CertApproval::on_cbx_clazz_currentTextChanged(const QString &arg1)
{
    if (arg1 != clazz_name && arg1 != "选择班次") {
        clazz_name = arg1;
        loadApprovalData();
    }
    if (arg1 == "选择班次") {
        clazz_name = "";
    }
}


void CertApproval::on_resetFilterBtn_clicked()
{
    ui->cbx_clazz->setCurrentIndex(0);
    loadApprovalData();
}
