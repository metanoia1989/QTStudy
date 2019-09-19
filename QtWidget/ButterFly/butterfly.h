#ifndef BUTTERFLY_H
#define BUTTERFLY_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>

class Butterfly : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Butterfly(QObject *parent = nullptr);
    void timerEvent(QTimerEvent *);	// 定时器实现动画
    QRectF boundingRect() const;	// 为图元限定区域范围，所有继承自QGraphicsItem的自定义图元必须实现此函数

signals:

public slots:

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
        QWidget *widget);	// 重绘函数

private:
    bool up;	// 标志蝴蝶翅膀的位置，以便实现动态效果
    QPixmap pix_up;		// 用于表示两幅蝴蝶的图片
    QPixmap pix_down;
    qreal angle;
};

#endif // BUTTERFLY_H
