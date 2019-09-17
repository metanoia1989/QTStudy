#include "shapewidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QBitmap>

ShapeWidget::ShapeWidget(QWidget *parent)
    : QWidget(parent)
{
    QPixmap pix;  // 新建一个 QPixmap 对象
    pix.load("16.png", nullptr, Qt::AvoidDither|Qt::ThresholdDither
     |Qt::ThresholdAlphaDither); // 为 Qixmap 对象填入图像
    resize(pix.size()); // 重设主窗体大小为所读取的图片的大小
    setMask(QBitmap(pix.mask()));	// 为控件添加遮罩，遮住所选区域以外的部分
}

ShapeWidget::~ShapeWidget()
{

}


// 实现控件的移动
void ShapeWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    } else if (event->button() == Qt::RightButton) {
        close();
    }
}

void ShapeWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}


// 重绘控件
void ShapeWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap("16.png"));
}
