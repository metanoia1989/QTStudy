#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "moveablechild.h"
#include <QMouseEvent>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    MoveableChild *mChild;
};
#endif // WIDGET_H
