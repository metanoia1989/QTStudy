#include "dropeventedit.h"
#include <QDebug>

DropEventEdit::DropEventEdit(QWidget *parent) : QLineEdit(parent)
{
}

void DropEventEdit::mouseMoveEvent(QMouseEvent *event)
{
    if( isReadOnly() )
    {
      // Restore override cursor.

    }
    qDebug() << "lineEdit: " << QString::number(event->pos().x());
    qDebug() << "lineEdit: " << QString::number(event->pos().y());
setCursor(Qt::ClosedHandCursor);
//    return event->ignore();
}
