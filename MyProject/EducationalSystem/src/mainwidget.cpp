#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "informationlist.h"
#include <QListWidget>
#include <QStackedWidget>

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
}

MainWidget::~MainWidget()
{
    delete ui;
}
