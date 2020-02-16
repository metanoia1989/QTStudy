#include "widget.h"
#include <QDebug>
#include <QLineEdit>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(500, 500);
    mChild = new MoveableChild(this);
//    mChild->setAttribute(Qt::WA_TransparentForMouseEvents);

    auto line = new QLineEdit(this);
    line->setAttribute(Qt::WA_TransparentForMouseEvents);
    setCursor(Qt::ClosedHandCursor);
}

Widget::~Widget()
{
}


void Widget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "parent: " << event->globalX() << event->globalY();
}
