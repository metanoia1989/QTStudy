#ifndef STARITEM_H
#define STARITEM_H

#include <QGraphicsItem>
#include <QPainter>

class StarItem : public QGraphicsItem
{
public:
    StarItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPixmap pix;
};


#endif // STARITEM_H
