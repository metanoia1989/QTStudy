#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 数量和单价两个SpinBox的valueChanged()信号与on_BtnCal_clicked() 槽关联
    // spinDec、spinBin、spinHex 的 valueChanged() 信号与其对应的按钮关联
}

Widget::~Widget()
{
    delete ui;
}

// 计算按键
void Widget::on_btnCal_clicked()
{
    int num = ui->spinNum->value();
    double price = ui->spinPrice->value();
    double total = num * price;
    ui->spinTotal->setValue(total); // 直接显示浮点数
}

// 读取十进制，以其他进制显示
void Widget::on_btnDec_clicked()
{
    int val;
    val = ui->spinDec->value();
    ui->spinBin->setValue(val);	// 自动以二进制显示
    ui->spinHex->setValue(val);	// 自动以十六进制显示
}


// 读取二进制，以其他进制显示
void Widget::on_btnBin_clicked()
{
    int val;
    val = ui->spinBin->value();
    ui->spinDec->setValue(val);
    ui->spinHex->setValue(val);
}

// 读取十六进制，以其他进制显示
void Widget::on_btnHex_clicked()
{
    int val;
    val = ui->spinHex->value();
    ui->spinDec->setValue(val);
    ui->spinBin->setValue(val);
}
