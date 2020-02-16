#ifndef MOVEABLECHILD_H
#define MOVEABLECHILD_H

#include <QWidget>
#include <QMouseEvent>

class MoveableChild : public QWidget
{
    Q_OBJECT
public:
    explicit MoveableChild(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:

};

#endif // MOVEABLECHILD_H
