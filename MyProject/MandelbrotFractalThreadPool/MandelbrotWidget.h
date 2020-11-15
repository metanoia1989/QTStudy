#pragma once

#include <QWidget>
#include <QPoint>
#include <QThread>
#include <QList>

class QResizeEvent;
class MandelbrotCalculator;

class MandelbrotWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MandelbrotWidget(QWidget *parent = nullptr);
    ~MandelbrotWidget();

private:
    MandelbrotCalculator mMandelbrotCalculator;
};
