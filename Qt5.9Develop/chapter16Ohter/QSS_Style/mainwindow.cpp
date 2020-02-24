#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStyleFactory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRegExp regExp(".(.*)\\+?Style");
    QString defaultStyle = QApplication::style()->metaObject()->className();
    ui->statusbar->showMessage(defaultStyle);

    if (regExp.exactMatch(defaultStyle)) {
        defaultStyle = regExp.cap(1);
    }
    ui->comboSysStyle->addItems(QStyleFactory::keys());
    ui->comboSysStyle->setCurrentIndex(ui->comboSysStyle->findText(defaultStyle, Qt::MatchContains));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboSysStyle_currentIndexChanged(const QString &arg1)
{
    QStyle *style = QStyleFactory::create(arg1);
    qApp->setStyle(style);
    ui->statusbar->showMessage(style->metaObject()->className());
}

// 正常样式，去掉所有样式表
void MainWindow::on_btnNormal_clicked()
{
    this->setStyleSheet("");
}

// 设置样式表
void MainWindow::on_btnStyleSheet_clicked()
{
    this->setStyleSheet("QPlainTextEdit {"
                        "color: blue; font: 13px '宋体'; }"
                        "QPushButton:hover { background-color:lime; }"
                        "QLineEdit { border: 2px groove red; "
                        "background-color: rab(170, 255, 127); "
                        "border-radius: 6px; }"
                        "QCheckBox:checked { color: red; }"
                        "QRadioButton:checked { color: red; }");
}

// 大字体
void MainWindow::on_btnFontLarge_clicked()
{
    ui->plainTextEdit->setStyleSheet("font: 13px '宋体';");
}

// 小字体
void MainWindow::on_btnFontSmall_clicked()
{
    ui->plainTextEdit->setStyleSheet("font: 10px '宋体';");
}
