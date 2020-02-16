#include "moveablechild.h"
#include <QDebug>

MoveableChild::MoveableChild(QWidget *parent) : QWidget(parent)
{
    resize(100, 100);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::red);
    setAutoFillBackground(true);
    setPalette(pal);
}

void MoveableChild::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "child" << event->globalX() << event->globalY();
}
