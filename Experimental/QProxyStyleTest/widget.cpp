#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initUI();
}

void Widget::initUI()
{
    ui->pushButton->setIcon(QIcon(":/icons/icons/homepage.svg"));
    ui->pushButton_2->setIcon(QIcon(":/icons/icons/category_network.svg"));
    ui->pushButton_3->setIcon(QIcon(":/icons/icons/category_chat.svg"));
    ui->pushButton_4->setIcon(QIcon(":/icons/icons/category_music.svg"));
    ui->pushButton_5->setIcon(QIcon(":/icons/icons/category_video.svg"));
    ui->pushButton_6->setIcon(QIcon(":/icons/icons/category_graphic.svg"));
    ui->pushButton_7->setIcon(QIcon(":/icons/icons/category_game.svg"));
    ui->pushButton_8->setIcon(QIcon(":/icons/icons/category_office.svg"));
    ui->pushButton_9->setIcon(QIcon(":/icons/icons/category_reading.svg"));
    ui->pushButton_10->setIcon(QIcon(":/icons/icons/category_develop.svg"));
    ui->pushButton_11->setIcon(QIcon(":/icons/icons/category_system.svg"));
    ui->pushButton_12->setIcon(QIcon(":/icons/icons/theme-symbolic.svg"));
    ui->pushButton_13->setIcon(QIcon(":/icons/icons/category_others.svg"));
    ui->pushButton_14->setIcon(QIcon(":/icons/icons/downloads-symbolic.svg"));
}

Widget::~Widget()
{
    delete ui;
}

