#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProgressBar>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QProgressBar *mProgressBar;
    QPushButton *mBtn;
    const int mMaxValue = 100;

signals:
    void updateValue(int value);

private slots:
    void btnClick();


};
#endif // WIDGET_H
