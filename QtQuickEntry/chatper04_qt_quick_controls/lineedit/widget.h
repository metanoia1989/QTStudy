#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QMouseEvent>
#include "dropeventedit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::Widget *ui;
    DropEventEdit *mLineEdit;
    QLabel *mLabel;
};
#endif // WIDGET_H
