#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QApplication>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    mLabel = new QLabel("占位用的", this);

    mLineEdit = new DropEventEdit(this);
    mLineEdit->setCursorMoveStyle(Qt::VisualMoveStyle);
//    mLineEdit->setReadOnly(true);
//    mLineEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);
    setMouseTracking(true);
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "widget: " << QString::number(event->pos().x());
    qDebug() << "widget: " << QString::number(event->pos().y());
    if (event->pos().x() < 200 && event->pos().y() < 200) {
        qDebug() << "触发事件了";
        setCursor(Qt::ClosedHandCursor);
//        setCursor(Qt::IBeamCursor); // 竖着的光标
    } else {
        setCursor(Qt::OpenHandCursor);
    }
}

Widget::~Widget()
{
    delete ui;
}

