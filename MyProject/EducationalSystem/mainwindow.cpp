#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "studentitemmodel.h"
#include <QSettings>
#include <QMessageBox>
#include <QDebug>
#include "HttpClient.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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

    QTimer::singleShot(0, this, &MainWindow::loadStudentData);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete httpClient;
}

/**
 * @brief MainWindow::initTableView
 */
void MainWindow::initTableView()
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
}

/**
 * 更新UI显示情况
 *
 * @brief MainWindow::updateUIStatus
 */
void MainWindow::updateUIStatus()
{
    if (per_page <= 1) {
        ui->prePageBtn->setDisabled(true);
    } else if (per_page == last_page) {
        ui->nextPageBtn->setDisabled(true);
    } else {
        ui->prePageBtn->setDisabled(false);
        ui->nextPageBtn->setDisabled(false);
    }
    ui->currentPageSpin->setValue(curr_page);
}

/**
 * 读取配置
 *
 * @brief MainWindow::readSettings
 */
void MainWindow::readSettings()
{
    QString iniPath =  QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings settings(iniPath, QSettings::IniFormat);
    settings.beginGroup("Site");
    server_url = settings.value("educational_site").toString();
    if (server_url.isEmpty()) {
        showError(tr("读取教务系统地址失败，请检查配置文件！"));
    }
    settings.endGroup();
}

/**
 * 展示错误信息
 *
 * @brief MainWindow::showError
 * @param msg
 */
void MainWindow::showError(QString msg)
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
 * @brief MainWindow::loadStudentData
 */
void MainWindow::loadStudentData()
{
    loading = true;
    QString student_list_url = server_url + "/api/desktop/educational";
    httpClient->get(student_list_url)
        .header("content-type", "application/json")
        .queryParam("page_size",per_page)
        .queryParam("page_num", curr_page)
        .onResponse(this, SLOT(showStudentData(QByteArray)))
        .onError(this, SLOT(showError(QString)))
        .timeout(10 * 1000) // 10s超时
        .exec();
}


void MainWindow::showStudentData(QByteArray result)
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
        QStandardItem *completeItem = new QStandardItem;
        if (studentItem["complete_material"].toInt() == 1) {
            completeItem->setData("已收齐", Qt::DisplayRole);
            completeItem->setData(QIcon(":/assets/icons/tick.png"), Qt::DecorationRole);
        } else {
            completeItem->setData("未收齐", Qt::DisplayRole);
            completeItem->setData(QIcon(":/assets/icons/cross.png"), Qt::DecorationRole);
        }

        QList<QStandardItem*> rowData = {
            new QStandardItem(studentItem["clazz_name"].toString()),
            new QStandardItem(studentItem["lecturer_name"].toString()), // 授课老师
            new QStandardItem(studentItem["assistant_name"].toString()), // 助教
            new QStandardItem(studentItem["student_name"].toString()),

            new QStandardItem(studentItem["identity_card"].toString()),
            new QStandardItem(studentItem["student_phone"].toString()),
            new QStandardItem(studentItem["recruiter"].toString()),
            completeItem,

            new QStandardItem(studentItem["data_sent"].toString()),
            new QStandardItem(studentItem["paper_photo"].toString()),
            new QStandardItem(studentItem["electronic_photo"].toString()),
            new QStandardItem(studentItem["education"].toString()),

            new QStandardItem(studentItem["sfzfyj"].toString()),
            new QStandardItem(studentItem["work_proof"].toString()),
            new QStandardItem(studentItem["social_data"].toString()),
            new QStandardItem(studentItem["graduation_status"].toString()),
        };
        model->appendRow(rowData);
    }
    ui->studentsDataTable->resizeColumnsToContents();
    ui->studentsDataTable->resizeRowsToContents();
    loading = false;
}


void MainWindow::on_refreshBtn_clicked()
{
    if (loading)  return;
    loadStudentData();
}

void MainWindow::on_nextPageBtn_clicked()
{
    if (loading || curr_page == last_page)  return;
    curr_page++;
    updateUIStatus();
    loadStudentData();
}

void MainWindow::on_prePageBtn_clicked()
{
    if (loading || curr_page <= 1)  return;
    curr_page--;
    updateUIStatus();
    loadStudentData();
}
