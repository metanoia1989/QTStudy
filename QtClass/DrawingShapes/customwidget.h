#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = nullptr);

private:
    QGraphicsView *mView;
    QGraphicsScene *mScene;
};

#endif // CUSTOMWIDGET_H
