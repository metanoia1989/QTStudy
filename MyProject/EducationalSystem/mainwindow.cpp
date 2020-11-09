#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QMessageBox>
#include <QDebug>
#include "HttpRequest.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , curr_page(1)
    , per_page(100)
{
    ui->setupUi(this);



    // 读取服务器地址
    readSettings();

}

MainWindow::~MainWindow()
{
    delete ui;
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
}

/**
 * 加载学员数据
 *
 * @brief MainWindow::loadStudentData
 */
void MainWindow::loadStudentData()
{

}

