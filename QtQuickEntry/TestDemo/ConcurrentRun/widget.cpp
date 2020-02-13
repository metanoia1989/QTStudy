#include "widget.h"
#include <QHBoxLayout>
#include <QtConcurrent/QtConcurrent>
#include <QThread>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    mBtn = new QPushButton("开始 ");
    mProgressBar = new QProgressBar();
    mProgressBar->setMaximum(mMaxValue);

    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(mProgressBar);
    hbox->addWidget(mBtn);
    setLayout(hbox);

//    connect(mBtn, &QPushButton::clicked, this, &Widget::btnClick, Qt::QueuedConnection);
    connect(mBtn, &QPushButton::clicked, this, &Widget::btnClick);
    connect(this, &Widget::updateValue, [&](int value) {
        mProgressBar->setValue(value);
    });
}

Widget::~Widget()
{
}

void Widget::btnClick()
{
    QtConcurrent::run([&] {
       while (true) {
           static int i = 0;
           i++;
           QMetaObject::invokeMethod(this, "updateValue",
                Qt::QueuedConnection, Q_ARG(int, i));

           if (i > this->mMaxValue) {
               break;
           }
       }
       qDebug() << QThread::currentThread();
    });
}
