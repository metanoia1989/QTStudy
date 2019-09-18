#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QPen>
#include <QBrush>

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = nullptr);
    // 所有的形状
    enum Shape{Line, Rectangle, RoundRect, Ellipse, Polygon, Polyline, Points, Arc, Path, Text, Pixmap};
    void setShape(Shape);	// 设置形状
    void setPen(QPen);	// 设置画笔
    void setBrush(QBrush);	// 设置画刷
    void setFillRule(Qt::FillRule);  // 设置填充模式
    void paintEvnet(QPaintEvent *);	// 重写重绘事件

private:
    Shape shape;
    QPen pen;
    QBrush brush;
    Qt::FillRule fillRule;

signals:

public slots:
};

#endif // PAINTAREA_H
