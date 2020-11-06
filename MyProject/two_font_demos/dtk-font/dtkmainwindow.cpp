#include "dtkmainwindow.h"
#include <QVBoxLayout>
#include <DWidget>
#include <QFontDatabase>

DTKMainWindow::DTKMainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    int font_id = QFontDatabase::addApplicationFont(":/fonts/萌喵酱.ttf");
    QString font_family = QFontDatabase::applicationFontFamilies(font_id).at(0);
    QFont sprout_cat(font_family);

    dBtnStyle = new DPushButton("这是一个带有字体样式的DPushButton");
    dBtnNone = new DPushButton("这是一个没有字体样式的DPushButton");
    qBtnStyle = new QPushButton("这是一个带有字体样式的QPushButton");
    qBtnNone = new QPushButton("这是一个没有字体样式的QPushButton");

    dBtnStyle->setFont(sprout_cat);
    qBtnStyle->setFont(sprout_cat);

    auto layout = new QVBoxLayout();
    layout->addWidget(dBtnStyle);
    layout->addWidget(dBtnNone);
    layout->addWidget(qBtnStyle);
    layout->addWidget(qBtnNone);

    DWidget *widget = new DWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
}

DTKMainWindow::~DTKMainWindow()
{
}

