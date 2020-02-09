#ifndef DROPEVENTEDIT_H
#define DROPEVENTEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QMouseEvent>

class DropEventEdit : public QLineEdit
{
    Q_OBJECT
public:
    DropEventEdit(QWidget *parent=nullptr);
    void mouseMoveEvent(QMouseEvent *) override;
};

#endif // DROPEVENTEDIT_H
