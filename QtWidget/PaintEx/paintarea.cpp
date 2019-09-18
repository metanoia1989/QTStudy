#include "paintarea.h"
#include <QPainter>

PaintArea::PaintArea(QWidget *parent) : QWidget(parent)
{
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    setMinimumSize(400, 400);
}

// 设置形状
void PaintArea::setShape(Shape s)
{
    shape = s;
    update();
}


// 设置画笔
void PaintArea::setPen(QPen p)
{
    pen = p;
    update();
}

// 设置画刷
void PaintArea::setBrush(QBrush b)
{
    brush = b;
    update();
}

// 设置填充模式
void PaintArea::setFillRule(Qt::FillRule rule)
{
    fillRule = rule;
    update();	// 重画绘制区窗体
}

void PaintArea::paintEvnet(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(pen);
    p.setBrush(brush);
    QRect rect(50, 100, 300, 200);	// 设置矩形区域，用来绘制各种图像
    static const QPoint points[4] = {
        QPoint(150, 100),
        QPoint(300, 150),
        QPoint(350, 250),
        QPoint(100, 300)
    };
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;
    QPainterPath path;	// 绘制路径
    path.addRect(150, 150, 100, 100);
    path.moveTo(100, 100);
    path.cubicTo(300, 100, 200, 200, 300, 300);
    path.cubicTo(100, 300, 200, 200, 100, 100);
    path.setFillRule(fillRule);
    switch (shape) {
        case Line:	// 直线
            p.drawLine(rect.topLeft(), rect.bottomRight()); break;
        case Rectangle:	// 长方形
            p.drawRect(rect);break;
        case RoundRect:	// 圆角方形
            p.drawRoundRect(rect);break;
        case Ellipse:	// 椭圆形
            p.drawEllipse(rect);break;
        case Polygon:	// 多边形
            p.drawPolygon(points, 4);break;
        case Polyline:	// 多边线
            p.drawPolyline(points, 4);break;
        case Points:	// 点
            p.drawPoints(points, 4);break;
        case Arc:	// 弧
            p.drawArc(rect, startAngle, spanAngle);break;
        case Path:	// 路径
            p.drawPath(path);break;
        case Text:	// 文字
            p.drawText(rect, Qt::AlignCenter, tr("Hello Qt!"));break;
        case Pixmap:	// 图片
            p.drawPixmap(150, 150, QPixmap("butterfly.png"));break;
    }
}
