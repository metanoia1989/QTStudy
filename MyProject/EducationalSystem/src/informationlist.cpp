#include "informationlist.h"
#include "ui_informationlist.h"
#include "studentitemmodel.h"
#include "utils/global.h"
#include "utils/cache.h"
#include "HttpClient.h"
#include <QMessageBox>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTimer>
#include <QProcess>

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
    model->setColumnCount(16);
    model->setDisableColumns({
        0, 1, 2, 3,
        4, 5, 6, 7
    });
    model->setHorizontalHeaderLabels({
        "班级名称", "授课老师", "助教老师", "学员姓名",
        "身份证号", "学员电话", "招生老师", "收齐情况",
        "教材是否寄出", "纸质版照片", "电子照", "学历扫描件",
        "身份证扫描件", "工作经历证明", "社保证明", "结业证"
    });
    ui->studentsDataTable->setModel(model);

    QFont font = QFont("微软雅黑", 12);
    font.setBold(true);
    ui->studentsDataTable->horizontalHeader()->setFont(font);

    connect(model, &QAbstractItemModel::dataChanged, this, &InformationList::cellDataChange);
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
            "clazz_name", "lecturer_name", "assistant_name", "student_name",
            "identity_card", "student_phone", "recruiter", "complete_material",
            "data_sent", "paper_photo", "electronic_photo", "education",
            "sfzfyj", "work_proof", "social_data", "graduation_status"
        };

        QList<QStandardItem*> rowData;
        for(auto &key: keys) {
            QStandardItem *item = new QStandardItem;
            // 设置显示的内容
            if (key == "complete_material") {
                if (studentItem[key].toInt() == 1) {
                    item->setData("已收齐", Qt::DisplayRole);
                    item->setData(QIcon(":/icons/tick.png"), Qt::DecorationRole);
                } else {
                    item->setData("未收齐", Qt::DisplayRole);
                    item->setData(QIcon(":/icons/cross.png"), Qt::DecorationRole);
                }
            } else {
                item->setData(studentItem[key].toString(), Qt::DisplayRole);
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
    qDebug() << QString("被修改的值为：%1# %2 -> %3").arg(studentId).arg(key).arg(value);
    QString student_list_url = QString("%1/api/desktop/educational/%2").arg(server_url).arg(studentId);
    QVariantMap data;
    data.insert(key, value);
    httpClient->put(student_list_url)
        .header("content-type", "application/json")
        .body(data)
        .onResponse([](QByteArray result) {
            qDebug() << result;
        })
        .onError(this, SLOT(showError(QString)))
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
    updateUIStatus();
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

void InformationList::on_refreshBtn_2_clicked()
{
    Global::cache()->setItem("autoLogin", "0");
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
    loadStudentData();
    updateUIStatus();
}
