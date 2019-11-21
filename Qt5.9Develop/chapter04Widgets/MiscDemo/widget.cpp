#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QPalette>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // SliderRed 之外的三个滑动条响应代码一样，只需要将其 valueChanged(int) 信号
    // 与 on_SliderRed_valueChanged() 关联即可
    connect(ui->SliderGreen, SIGNAL(valueChanged(int)), this,
        SLOT(on_SliderRed_valueChanged(int)));
    connect(ui->SliderBlue, SIGNAL(valueChanged(int)), this,
        SLOT(on_SliderRed_valueChanged(int)));
    connect(ui->SliderAlpha, SIGNAL(valueChanged(int)), this,
        SLOT(on_SliderRed_valueChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

// 拖动 Red、Green、Blue 颜色滑动条是设置 textEdit 的底色
void Widget::on_SliderRed_valueChanged(int value)
{
    Q_UNUSED(value);
    QColor color;
    int R = ui->SliderRed->value();
    int G = ui->SliderGreen->value();
    int B = ui->SliderBlue->value();
    int alpha = ui->SliderAlpha->value();
    color.setRgb(R, G, B, alpha);	// 生成颜色

    QPalette pal = ui->textEdit->palette();	// 获取 textEdit 原有的 palette
    pal.setColor(QPalette::Base, color);	// 设置palette的基色即背景色
    ui->textEdit->setPalette(pal);
}

// 滑动表盘组件的指针，设定的LCD的显示值等于表盘的值
void Widget::on_dial_valueChanged(int value)
{
    ui->LCDDisplay->display(value);
}

// 设置LCD显示十进制数
void Widget::on_radioBtnDec_clicked()
{
    ui->LCDDisplay->setDigitCount(3); // 设置位数
    ui->LCDDisplay->setDecMode();
}

// 设置LCD显示二进制数
void Widget::on_radioBtnBin_clicked()
{
    ui->LCDDisplay->setDigitCount(8);
    ui->LCDDisplay->setBinMode();
}

// 设置LCD显示八进制数
void Widget::on_radioBtnHex_clicked()
{
    ui->LCDDisplay->setDigitCount(4);
    ui->LCDDisplay->setOctMode();
}

// 设置LCD显示十六进制数
void Widget::on_radioBtnOct_clicked()
{
    ui->LCDDisplay->setDigitCount(3);
    ui->LCDDisplay->setHexMode();
}

// 垂直滑动标尺变化
void Widget::on_SliderV_valueChanged(int value)
{
    ui->progBarV->setValue(value);
    ui->ScrollBarV->setValue(value);
}

// 水平滑动标尺变化
void Widget::on_SliderH_valueChanged(int value)
{
    ui->progBarH->setValue(value);
    ui->ScrollBarH->setValue(value);
}

// 垂直滚动条移动
void Widget::on_ScrollBarV_sliderMoved(int position)
{
    ui->progBarV->setValue(position);
}

// 水平滚动条移动
void Widget::on_ScrollBarH_sliderMoved(int position)
{
    ui->progBarH->setValue(position);
}
