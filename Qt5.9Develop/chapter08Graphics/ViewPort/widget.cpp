#include "widget.h"
#include "ui_widget.h"

#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    this->resize(300, 300);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    int W = width();
    int H = height();

    int side = qMin(W, H);
    QRect rect((W-side)/2, (H-side)/2, side, side); // viewport 矩形区
    painter.drawRect(rect); // viewport 大小

    painter.setViewport(rect);	// 设置viewport
    painter.setWindow(-100, -100, 200, 200);	// 设置窗口大小，逻辑坐标
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置画笔
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    painter.setPen(pen);

    // 线性渐变
    QLinearGradient linearGrad(0, 0, 100, 0);	// 从左到右
    linearGrad.setColorAt(0, Qt::yellow);	// 起点颜色
    linearGrad.setColorAt(1, Qt::green);	// 终点颜色
    linearGrad.setSpread(QGradient::PadSpread);	 // 展布模式
    painter.setBrush(linearGrad);

    // 设置复合模式
//    painter.setCompositionMode(QPainter::CompositionMode_Difference);
    painter.setCompositionMode(QPainter::CompositionMode_Exclusion);
//    painter.setCompositionMode(QPainter::RasterOp_NotSource);

    for (int i = 0; i < 36; i++) {
        painter.drawEllipse(QPoint(50, 0), 50, 50);
        painter.rotate(10);
    }
}
