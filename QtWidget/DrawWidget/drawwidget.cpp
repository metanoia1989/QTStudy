#include "drawwidget.h"
#include <QPen>

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true); // 设置窗体背景色
    setPalette(QPalette(Qt::white));
    pix = new QPixmap(size());	// 随时接收绘制的内容
    pix->fill(Qt::white);	// 填充背景色为白色
    setMinimumSize(600, 400);	// 设置绘制区窗体的最小尺寸
}

// 接收主窗口传来的线型风格参数
void DrawWidget::setStyle(int s)
{
    style = s;
}


// 接收主窗口传来的线宽风格参数
void DrawWidget::setWidth(int s)
{
    weight = s;
}

// 接收主窗口传来的画笔颜色值
void DrawWidget::setColor(QColor c)
{
    color = c;
}

// 按下鼠标按键时，记录当前的鼠标位置值
void DrawWidget::mousePressEvent(QMouseEvent *e)
{
    startPos = e->pos();
}

// 追踪鼠标移动事件
void DrawWidget::mouseMoveEvent(QMouseEvent *e)
{
    QPainter *painter = new QPainter;
    QPen pen;
    pen.setStyle((Qt::PenStyle) style);	// 设置画笔的线型，style 为当前选择的线型
    pen.setWidth(weight);	// 设置画笔的线宽值
    pen.setColor(color);	// 设置画笔的颜色
    painter->begin(pix);	// 绘制开始
    painter->setPen(pen);
    // 绘制从 startPos 到鼠标当前位置的直线
    painter->drawLine(startPos, e->pos());
    painter->end();
    startPos = e->pos();
    update();	// 重绘绘制区窗体
}

// 接收图形绘制的 QPixmap 对象绘制在绘制区窗体控件上
void DrawWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0, 0), *pix);
}

// 窗体大小变化时，进行重绘
void DrawWidget::resizeEvent(QResizeEvent *event)
{
    if (height() > pix->height() || width() > pix->width()) {
        QPixmap *newPix = new QPixmap(size());
        newPix->fill(Qt::white);
        QPainter p(newPix);
        p.drawPixmap(QPoint(0, 0), *pix);
        pix = newPix;
    }
    QWidget::resizeEvent(event);
}

// 完成绘制区的清除操作
void DrawWidget::clear()
{
    QPixmap *clearPix = new QPixmap(size());
    clearPix->fill(Qt::white);
    pix = clearPix;
    update();
}
