#ifndef DIGICLOCK_H
#define DIGICLOCK_H

#include <QLCDNumber>


class DigiClock : public QLCDNumber
{
    Q_OBJECT
public:
    DigiClock(QWidget *parent=nullptr);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

public slots:
    void showTime();	// 显示当前时间

private:
    QPoint dragPosition; 	// 保存鼠标点击先谷底电子时钟窗体左上角的偏移值
    bool showColon;	// 用于显示时间是否显示 ":"
};

#endif // DIGICLOCK_H
