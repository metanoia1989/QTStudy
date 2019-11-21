#include "widget.h"
#include "ui_widget.h"
#include <QString>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

// 从界面上分别读取数量和价格，计算结果再显示到文本框里
void Widget::on_btnCel_clicked()
{
    QString str = ui->editNum->text();	// 读取数量
    int num = str.toInt();
    str = ui->editPrice->text();	// 读取单价
    double price = str.toDouble();
    double total = num * price;
    str = str.sprintf("%.2f", total);
    ui->editTotal->setText(str);
}

// 读取十进制数转换为二进制和十六进制字符串
void Widget::on_btnDec_clicked()
{
    QString str = ui->editDec->text();
    int val = str.toInt();	// 默认为十进制

    str = str.setNum(val, 16); // 转换为16进制
    str = QString::number(val, 16);
    ui->editHex->setText(str.toUpper());

    str = str.setNum(val, 2);	// 转换为2进制
    str = QString::number(val, 2);
    ui->editBin->setText(str);
}

// 读取二进制，转换为十进制和十六进制
void Widget::on_btnBin_clicked()
{
    QString str = ui->editBin->text();	// 读取二进制字符串
    bool ok;
    int val = str.toInt(&ok, 2);	// 以二进制读入

    str = QString::number(val, 10);	// 转换为十进制
    ui->editDec->setText(str);
    str = QString::number(val, 16);	// 转换为十六进制
    ui->editHex->setText(str.toUpper());
}

// 读取十六进制，转换为十进制和二进制
void Widget::on_btnHex_clicked()
{
    QString str = ui->editHex->text();	// 读取十六进制字符串
    bool ok;
    int val = str.toInt(&ok, 16);	// 以十六进制读入

    str = QString::number(val, 10);	// 转换为十进制
    ui->editDec->setText(str);
    str = QString::number(val, 2);	// 转换为二进制
    ui->editBin->setText(str);

}
