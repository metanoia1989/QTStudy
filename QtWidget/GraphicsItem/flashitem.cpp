#include "flashitem.h"

FlashItem::FlashItem(QObject *parent) : QObject(parent)
{
    flash = true;	// 为颜色切换标识赋初值
    setFlag(ItemIsMovable);
    startTimer(1000);	//启动定时器，1000毫秒
}

QRectF FlashItem::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(-10-adjust, -10-adjust, 43+adjust, 43+adjust);
}

// 重绘图元
void FlashItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);	// 闪烁图元的阴影区不绘制边线
    painter->setBrush(Qt::darkGray);	// 闪烁图元的阴影区的阴影画刷颜色为深灰
    painter->drawEllipse(-7,-7,40,40);	// 绘制阴影区
    painter->setPen(QPen(Qt::black, 0));	// 闪烁区的椭圆边线颜色为黑色，线宽为0
    painter->setBrush(flash?(Qt::red):(Qt::yellow));	// 闪烁区颜色根据切换标识决定填充那种颜色
    painter->drawEllipse(-10,-10,40,40);	// 绘制与阴影区同样形状和大小的椭圆，错开一定距离实现立体感
}

// 定时器响应函数完成颜色切换标识的反置，每次反置后调用update()函数重绘图元以实现闪烁的效果
void FlashItem::timerEvent(QTimerEvent *)
{
    flash = !flash;
    update();
}
