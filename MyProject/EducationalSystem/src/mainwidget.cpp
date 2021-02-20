#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "informationlist.h"
#include <QListWidget>
#include <QStackedWidget>
#include <QTimer>
#include <QSimpleUpdater.h>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    // 初始化界面
    connect(ui->listWidget, &QListWidget::currentRowChanged,
            ui->stackedWidget, &QStackedWidget::setCurrentIndex);
    // 去掉边框
    ui->listWidget->setFrameShape(QListWidget::NoFrame);
    // 隐藏滚动条
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 检测应用更新
    QTimer::singleShot(3000, this, &MainWidget::checkAppUpdate);
}

MainWidget::~MainWidget()
{
    delete ui;
}

/**
 * @brief 检测应用升级
 */
void MainWidget::checkAppUpdate()
{
    qDebug() << "检测应用升级更新，当前程序版本：" << qApp->applicationVersion();
    m_updater = QSimpleUpdater::getInstance();
    QString DEFS_URL = "http://azxfpx.com/educational_app/updates.json";
    m_updater->checkForUpdates(DEFS_URL);
}
