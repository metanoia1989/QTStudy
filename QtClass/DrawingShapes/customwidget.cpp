#include "customwidget.h"
#include <QVBoxLayout>
#include <QGraphicsItem>

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{
    mView = new QGraphicsView(this);
    mScene = new QGraphicsScene(this);
    mView->setScene(mScene);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(mView);
    setLayout(layout);

    QGraphicsItem *rect1 = mScene->addRect(0, 0, 40, 40,
                   Qt::NoPen, QColor("#ffbb33"));
    rect1->setFlags(QGraphicsItem::ItemIsFocusable|
                    QGraphicsItem::ItemIsMovable);
}
