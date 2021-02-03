#include "about.h"
#include "ui_about.h"
#include <QApplication>

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    ui->app_version->setText(QString("程序版本：v%1").arg(qApp->applicationVersion()));
}

About::~About()
{
    delete ui;
}
