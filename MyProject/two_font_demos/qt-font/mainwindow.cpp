#include "mainwindow.h"
#include <QHBoxLayout>
#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    int font_id = QFontDatabase::addApplicationFont(":/fonts/萌喵酱.ttf");
    QString font_family = QFontDatabase::applicationFontFamilies(font_id).at(0);
    QFont sprout_cat(font_family);

    btnStyle = new QPushButton("这是一个带有字体样式的QPushButton");
    btnNone = new QPushButton("这是一个没有字体样式的QPushButton");
    btnStyle->setFont(sprout_cat);

    auto layout = new QHBoxLayout();
    layout->addWidget(btnStyle);
    layout->addWidget(btnNone);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
}

