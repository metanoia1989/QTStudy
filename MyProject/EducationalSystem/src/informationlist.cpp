#include "informationlist.h"
#include "ui_informationlist.h"
#include "studentitemmodel.h"
#include "checkboxheader.h"
#include "delegate/certificatedelegate.h"
#include "delegate/collectiondelegate.h"
#include "delegate/datedelegate.h"
#include "delegate/paperphotodelegate.h"
#include "delegate/techmaterialdelegate.h"

#include "utils/global.h"
#include "utils/cache.h"
#include "utils/threads.h"
#include "HttpClient.h"

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

InformationList::InformationList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InformationList)
    , curr_page(1)
    , per_page(100)
    , last_page(100)
    , loading(false)
{
    ui->setupUi(this);
    initTableView();

    httpClient = new AeaQt::HttpClient;


    // 读取服务器地址
    readSettings();

    QTimer::singleShot(0, this, &InformationList::loadStudentData);
    loadFilterData();
}

InformationList::~InformationList()
{
    delete ui;
    delete httpClient;
}

/**
 * @brief InformationList::initTableView
 */
void InformationList::initTableView()
{

    model = new StudentItemModel(this);
    model->setColumnCount(17);
    model->setDisableColumns({
        0, 1, 2, 3,
        4, 5, 6, 7,
        8, 9
    });
    model->setMaterialColumns({
        12, 13, 14,
        15, 16, 17
    });
    model->setMaterialCompleteColumn(8);
    model->setHorizontalHeaderLabels({
        "     学员ID",
        "班级名称", "授课老师", "助教老师", "学员姓名",
        "身份证号", "学员电话", "招生老师", "收齐情况",
        "资料未收齐情况",
         "资料收齐备注",
        "教材是否寄出", "纸质版照片", "电子照", "学历扫描件",
        "身份证扫描件", "工作经历证明", "社保证明", "结业证",
        "结业证寄件日期", "结业证寄件备注"
    });

    ui->studentsDataTable->setModel(model);
    ui->studentsDataTable->setAlternatingRowColors(true);
    ui->studentsDataTable->setStyleSheet("QTableView{background-color: #fff;"
    "alternate-background-color: #f3f3f3;}");

    // 设置教材是否寄出 第11列
    ui->studentsDataTable->setItemDelegateForColumn(11, new TechMaterialDelegate(this));
    // 设置纸质版照片 第12列
    ui->studentsDataTable->setItemDelegateForColumn(12, new PaperPhotoDelegate(this));
    // 其他资料相关字段 第13~17列
    for (int i = 13;  i<=17; i++) {
        ui->studentsDataTable->setItemDelegateForColumn(i, new CollectionDelegate(this));
    }
    // 设置结业证寄出列的下拉菜单 第18列
    ui->studentsDataTable->setItemDelegateForColumn(18, new CertificateDelegate(this));
    // 设置结业证寄出日期  第19列
    ui->studentsDataTable->setItemDelegateForColumn(19, new DateDelegate(this));

    QFont font = QFont("微软雅黑", 12);
    font.setBold(true);
    ui->studentsDataTable->horizontalHeader()->setFont(font);

    // 数据变化时，请求后端更新
    connect(model, &QAbstractItemModel::dataChanged, this, &InformationList::cellDataChange);

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

    // 设置右键菜单
    menu = new QMenu(ui->studentsDataTable);
//    QAction *approvalAction = new QAction("申请资料收齐"); // 不需要申请了，自动处理
    QAction *certAction = new QAction("申请结业证书已寄");
    QAction *collectionAction = new QAction("设置资料字段已收齐");
    menu->addActions({ certAction, collectionAction  });

    ui->studentsDataTable->setContextMenuPolicy(Qt::CustomContextMenu);

//    connect(approvalAction, &QAction::triggered, [this](){
//        materialProcessRequest("sponsorMaterialComplete");
//    });
    connect(certAction, &QAction::triggered, [this](){
        materialProcessRequest("sponsorCertSend");
    });
    connect(collectionAction, &QAction::triggered, [this](){
        int result = QMessageBox::information(this, "确认提示", "确认要设置为已收齐吗？", tr("确认"), tr("取消"));
        if (result == tr("确定").toInt()) {
            materialProcessRequest("setMaterialComplete");
        }
    });
    connect(ui->studentsDataTable, &QTableView::customContextMenuRequested,
                this, &InformationList::ProvideContextMenu);

    // 设置批处理的右键菜单
    batchMenu = new QMenu(this);
//    QAction *approvalBatAct = new QAction("批量申请资料收齐");
    QAction *certBatAct = new QAction("批量申请结业证书已寄");
    QAction *collectionBatAct = new QAction("批量设置资料字段已收齐");
    QAction *remarkBatAct = new QAction("批量更新资料收齐备注");
    batchMenu->addActions({ certBatAct, collectionBatAct, remarkBatAct});
    ui->batchBtn->setMenu(batchMenu);
//    connect(approvalBatAct, &QAction::triggered, [this](){
//        materialProcessBatch("sponsorMaterialComplete");
//    });
    connect(certBatAct, &QAction::triggered, [this](){
        materialProcessBatch("sponsorCertSend");
    });
    connect(collectionBatAct, &QAction::triggered, [this](){
        int result = QMessageBox::information(this, "确认提示", "确认要设置为已收齐吗？", tr("确认"), tr("取消"));
        if (result == tr("确定").toInt()) {
            materialProcessBatch("setMaterialComplete");
        }
    });
    connect(remarkBatAct, &QAction::triggered, [this](){
        bool ok;
        QString text = QInputDialog::getText(this, "批量更新资料收齐备注", "资料收齐备注内容", QLineEdit::Normal, "", &ok);
        if (ok) {
            remark = text;
            materialProcessBatch("setMaterialRemark");
        }
    });
}

/**
 * 更新UI显示情况
 *
 * @brief InformationList::updateUIStatus
 */
void InformationList::updateUIStatus()
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
void InformationList::loadFilterData()
{

    class GetTokenRunnable : public QObject
    {
        InformationList * m_p;
        QString m_token;
    public:
        GetTokenRunnable(InformationList * p, QString token)
            : m_p(p), m_token(token)
        {
        }

        void run(DataType type)
        {

            QString filter_data_url = getServerUrl() + "/api/desktop/%1";
            if (type == DataType::ClazzData) {
                filter_data_url = filter_data_url.arg("clazz");
            } else if (type == DataType::LecturerData) {
                filter_data_url = filter_data_url.arg("lecturer");
            } else if (type == DataType::RecruiterData) {
                filter_data_url = filter_data_url.arg("recruiter");
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
    ExecuteOnThread(THREAD_NETWORK, [=](){
        GetTokenRunnable runnable(this, token);
        runnable.run(DataType::LecturerData);
    });
    ExecuteOnThread(THREAD_DOWNLOAD, [=](){
        GetTokenRunnable runnable(this, token);
        runnable.run(DataType::ClazzData);
    });
    ExecuteOnThread(THREAD_SEARCH, [=](){
        GetTokenRunnable runnable(this, token);
        runnable.run(DataType::RecruiterData);
    });
    connect(this, &InformationList::filterDataLoaded, this, &InformationList::showFilterData, Qt::QueuedConnection);
    connect(this, &InformationList::requestShowError, this, &InformationList::showError, Qt::QueuedConnection);
}

/**
 * @brief 获取选中的学员ID
 * @return QList<int>
 */
QList<int> InformationList::getSelectedIds()
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
void InformationList::showFilterData(DataType type, QStringList data)
{
    if (type == DataType::ClazzData) {
        ui->cbx_clazz->clear();
        ui->cbx_clazz->addItem("选择班次");
        ui->cbx_clazz->addItems(data);
    } else  if (type == DataType::LecturerData) {
        ui->cbx_lecturer->clear();
        ui->cbx_lecturer->addItem("选择授课老师");
        ui->cbx_lecturer->addItems(data);
    } else  if (type == DataType::RecruiterData) {
        ui->cbx_recruiter->clear();
        ui->cbx_recruiter->addItem("选择招生老师");
        ui->cbx_recruiter->addItems(data);
    }
}

/**
 * 读取配置
 *
 * @brief InformationList::readSettings
 */
void InformationList::readSettings()
{
    server_url = getServerUrl();
    if (server_url.isEmpty()) {
        showError(tr("读取教务系统地址失败，请检查配置文件！"));
    }
}

/**
 * 展示错误信息
 *
 * @brief InformationList::showError
 * @param msg
 */
void InformationList::showError(QString msg)
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
 * @brief InformationList::loadStudentData
 */
void InformationList::loadStudentData()
{
    loading = true;
    QString student_list_url = server_url + "/api/desktop/educational";
    QString token = Global::cache()->getItem("token");
    httpClient->get(student_list_url)
        .header("content-type", "application/json")
        .header("authorization", QString("Bearer %1").arg(token))
        .queryParam("page_size",per_page)
        .queryParam("page_num", curr_page)
        .queryParam("keyword", keyword)
        .queryParam("clazz_name", clazz_name)
        .queryParam("recruiter_name", recruiter_name)
        .queryParam("lecturer_name", lecturer_name)
        .onResponse(this, SLOT(showStudentData(QByteArray)))
        .onError(this, SLOT(showError(QString)))
        .timeout(10 * 1000) // 10s超时
        .exec();
}


void InformationList::showStudentData(QByteArray result)
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
            "id",
            "clazz_name", "lecturer_name", "assistant_name", "student_name",
            "identity_card", "student_phone", "recruiter", "complete_material",
            "material_situation", "material_remark",
            "data_sent", "paper_photo", "electronic_photo", "education",
            "sfzfyj", "work_proof", "social_data", "graduation_status",
            "cert_mail_date", "cert_mail_remark"
        };

        QList<QStandardItem*> rowData;
        for(auto &key: keys) {
            QStandardItem *item = new QStandardItem;
            // 设置显示的内容
            if (key == "complete_material") { // 标志整个资料的收齐状态
                if (studentItem[key].toInt() == 1) {
                    item->setData("已收齐", Qt::DisplayRole);
                    item->setData(QIcon(":/icons/tick.png"), Qt::DecorationRole);
                } else {
                    item->setData("未收齐", Qt::DisplayRole);
                    item->setData(QIcon(":/icons/cross.png"), Qt::DecorationRole);
                }
            } else if (key == "material_remark") { // 资料收齐备注
                item->setData(studentItem[key].toString(), Qt::DisplayRole);
                item->setData(QColor(209, 228, 240), Qt::BackgroundColorRole);
            } else if (key == "graduation_status") { // 结业证寄出状态
                item->setData(studentItem[key].toString(), Qt::EditRole);
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
 * 单元格数据被修改
 *
 * @brief InformationList::cellDataChange
 * @param topLeft
 * @param bottomRight
 */
void InformationList::cellDataChange(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    Q_UNUSED(bottomRight);
    QModelIndex index = model->index(topLeft.row(), topLeft.column());
    QStandardItem *item = model->itemFromIndex(index);
    int studentId = item->data(Qt::UserRole + 1).value<int>();
    QString key = item->data(Qt::UserRole + 2).value<QString>();
    QString value = item->data(Qt::DisplayRole).value<QString>();

    if (key == "complete_material" || key == "material_situation") {
        return;
    }

    if (key == "id") {
        int checked = 0;
        int unchecked = 0;
        for (int i = 0; i < model->rowCount(); i++) {
            if (model->item(i, 0)->checkState() == Qt::Checked) {
                checked++;
            } else if (model->item(i, 0)->checkState() == Qt::Unchecked) {
                unchecked++;
            }
            if (checked > 0 && unchecked > 0) {
                header->updateCheckState(QStyle::State_NoChange);
            } else if (checked > 0) {
                header->updateCheckState(QStyle::State_On);
            } else {
                header->updateCheckState(QStyle::State_Off);
            }
        }
        return;
    }

    // 资料相关字段变化时，自动计算资料未收齐情况
    QString materialSituation = "";
    QList<int> materialColumns = model->getMaterialColumns(); // 资料字段
    QList<QString> completeStatus = { "已收齐", "提前提交" }; // 资料收齐状态
    QStringList inComplete;
    if (materialColumns.indexOf(topLeft.column()) != -1) {
        for (int i=0; i<materialColumns.count(); i++) {
            int column = materialColumns.at(i);
            QString label = model->headerData(column, Qt::Horizontal).toString();
            QString text = column == topLeft.column() ? value : model->itemFromIndex(
                model->index(topLeft.row(), column))->data(Qt::EditRole).toString();
            if (completeStatus.indexOf(text) == -1) {
                inComplete.append(label);
            }
        }
    }
    if (!inComplete.isEmpty()) {
        materialSituation = inComplete.count() == materialColumns.count()
            ? "全部缺少" : QString("缺%1").arg(inComplete.join(", "));
        qDebug() << "资料收集情况说明：" <<  QString("缺%1").arg(inComplete.join(", "));
    } else {
        materialSituation = "全部收齐";
    }
    int inCompleteColumn = model->getMaterialCompleteColumn() + 1;
    auto tItem = model->itemFromIndex(model->index(topLeft.row(), inCompleteColumn));
    tItem->setData(materialSituation, Qt::EditRole);

    qDebug() << QString("被修改的值为：%1# %2 -> %3").arg(studentId).arg(key).arg(value);
    QString student_list_url = QString("%1/api/desktop/educational/%2").arg(server_url).arg(studentId);
    QVariantMap data;
    data.insert(key, value);

    qDebug() << "请求数据为：" << data;
    QString token = Global::cache()->getItem("token");
    httpClient->put(student_list_url)
        .header("content-type", "application/json")
        .header("authorization", QString("Bearer %1").arg(token))
        .body(data)
        .onResponse([this](QByteArray result) {
            qDebug() << result;
            QJsonObject json = QJsonDocument::fromJson(result).object();
            if (json.isEmpty()) {
                return showError("服务器响应为空！");
            }
            if (json["code"].toInt() != 0) {
                return showError(json["msg"].toString());
            }
        })
        .onError(this, SLOT(showError(QString)))
        .timeout(10 * 1000) // 10s超时
            .exec();
}

/**
 * @brief 提供右键菜单
 * @param position
 */
void InformationList::ProvideContextMenu(const QPoint& position)
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
void InformationList::materialProcessRequest(QString type)
{
    if (loading) return;
    QList<QString> types = {
        "setMaterialComplete",
        "sponsorMaterialComplete",
        "sponsorCertSend"
    };
    if (types.indexOf(type) == -1) {
        return showError("未知的资料收齐类型！");
    }
    if (selectedId == 0) {
        return showError("无效的学员ID！");
    }

    loading = true;
    QString url = server_url + "/api/desktop/educational/%1";
    QString token = Global::cache()->getItem("token");
    qDebug() << "发起请求：" << url.arg(type);
    QVariantMap data;
    data.insert("student_id", selectedId);
    httpClient->post(url.arg(type))
        .header("content-type", "application/json")
        .header("authorization", QString("Bearer %1").arg(token))
        .body(data)
        .onResponse([this, type](QByteArray result){
            loading = false;
            selectedId = 0;
            QJsonObject json = QJsonDocument::fromJson(result).object();
            if (json.isEmpty()) {
                return showError("服务器响应为空！");
            }
            if (json["code"].toInt() != 0) {
                return showError(json["msg"].toString());
            }
            if (type == "setMaterialComplete") {
                // 设置资料字段为已收齐，重新加载页面 or 将当前行的几个资料字段设置为已收齐
                loadStudentData();
            }
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
void InformationList::materialProcessBatch(QString type)
{
    if (loading) return;
    QList<QString> types = {
        "setMaterialComplete",
        "sponsorMaterialComplete",
        "sponsorCertSend",
        "setMaterialRemark"
    };
    if (types.indexOf(type) == -1) {
        return showError("未知的资料收齐类型！");
    }
    QList<int> studentIds = getSelectedIds();
    if (studentIds.empty()) {
        return showError("没有选中任何学员！");
    }
    QStringList id_list;
    for(int i = 0; i < studentIds.count(); i++) {
        id_list << QString::number(studentIds.at(i));
    }
    QString ids = id_list.join(",");

    loading = true;
    QString url = server_url + "/api/desktop/educational/%1";
    url = url.arg(type);
    QString token = Global::cache()->getItem("token");
    qDebug() << "发起请求：" << url;
    QVariantMap data;
    data.insert("student_id", ids);
    if (type == "setMaterialRemark") {
        data.insert("remark", remark);
    }

    httpClient->post(url)
        .header("content-type", "application/json")
        .header("authorization", QString("Bearer %1").arg(token))
        .body(data)
        .onResponse([this, type](QByteArray result){
            loading = false;
            remark = "";
            QJsonObject json = QJsonDocument::fromJson(result).object();
            if (json.isEmpty()) {
                return showError("服务器响应为空！");
            }
            if (json["code"].toInt() != 0) {
                return showError(json["msg"].toString());
            }
            if (type == "setMaterialComplete" || type == "setMaterialRemark") {
                // 设置资料字段为已收齐，重新加载页面 or 将当前行的几个资料字段设置为已收齐
                loadStudentData();
            }
            return showSuccessMsg(json["msg"].toString());
        })
        .onError([this](QString errorStr){
            loading = false;
            remark = "";
            showError(errorStr);
        })
        .timeout(10 * 1000) // 10s超时
            .exec();
}


void InformationList::on_refreshBtn_clicked()
{
    if (loading)  return;
    loadStudentData();
}

void InformationList::on_nextPageBtn_clicked()
{
    if (loading || curr_page == last_page)  return;
    curr_page++;
    updateUIStatus();
    loadStudentData();
}

void InformationList::on_prePageBtn_clicked()
{
    if (loading || curr_page <= 1)  return;
    curr_page--;
    loadStudentData();
}

/**
 * 用户按下回车键
 * @brief InformationList::on_lineEdit_returnPressed
 */
void InformationList::on_lineEdit_returnPressed()
{
    if (loading) return;
    loading = true;
    keyword = ui->lineEdit->text().trimmed();
    loadStudentData();
}

/**
 * 点击搜索框
 * @brief InformationList::on_searchBtn_clicked
 */
void InformationList::on_searchBtn_clicked()
{
    if (loading) return;
    loading = true;
    keyword = ui->lineEdit->text().trimmed();
    loadStudentData();
}

/**
 * @brief 点击注销按钮
 */
void InformationList::on_logoutBtn_clicked()
{
    Global::cache()->setItem("autoLogin", "0");
    Global::cache()->setItem("token", "");
    qApp->closeAllWindows();
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
}

void InformationList::on_cb_pageSize_currentIndexChanged(const QString &arg1)
{
    int num = arg1.toInt();
    if (num == per_page || loading) {
        return;
    }
    per_page = num;
    curr_page = 1;
    loadStudentData();
}

void InformationList::on_cbx_clazz_currentTextChanged(const QString &arg1)
{
    if (arg1 != clazz_name && arg1 != "选择班次") {
        clazz_name = arg1;
        loadStudentData();
    }
    if (arg1 == "选择班次") {
        clazz_name = "";
    }
}

void InformationList::on_cbx_recruiter_currentTextChanged(const QString &arg1)
{
    if (arg1 != recruiter_name && arg1 != "选择招生老师") {
        recruiter_name = arg1;
        loadStudentData();
    }
    if (arg1 == "选择招生老师") {
        recruiter_name = "";
    }
}

void InformationList::on_cbx_lecturer_currentTextChanged(const QString &arg1)
{
    if (arg1 != lecturer_name && arg1 != "选择授课老师") {
        lecturer_name = arg1;
        loadStudentData();
    }
    if (arg1 == "选择授课老师") {
        lecturer_name = "";
    }
}
