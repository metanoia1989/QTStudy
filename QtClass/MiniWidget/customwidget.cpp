#include "customwidget.h"
#include <QPainter>

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{

}

void CustomWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QRect r1 = rect().adjusted(10, 10, -10, -10);
    painter.setPen(QColor("#33b5e5"));
    painter.drawRect(r1);

    QRect r2(QPoint(0, 0), QSize(40, 40));
    if (mLastPos.isNull()) {
        r2.moveCenter((r1.center()));
    } else {
        r2.moveCenter(mLastPos);
    }
    painter.fillRect(r2, QColor("#ffbb33"));
}

void CustomWidget::mousePressEvent(QMouseEvent *event)
{
    mLastPos = event->pos();
    update();
}

void CustomWidget::mouseMoveEvent(QMouseEvent *event)
{
    mLastPos = event->pos();
    update();
}
