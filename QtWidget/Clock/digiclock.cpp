#include "digiclock.h"
#include <QTimer>
#include <QTime>
#include <QMouseEvent>

DigiClock::DigiClock(QWidget *parent) : QLCDNumber (parent)
{
    /* 设置时钟背景 */
    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::blue); // 电子时钟窗体的背景色设置
    setPalette(p);
    setWindowFlag(Qt::FramelessWindowHint); // 设置窗体的标识，无边框面板和标题栏的窗体
    setWindowOpacity(0.5); // 设置窗体透明度,在X11系统无效
    QTimer *timer = new QTimer(this);	// 定时器对象
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime())); // 连接定时器的timeout()信号与显示时间的槽函数showTime()
    timer->start(1000); // 以 1000 毫秒为周期启动定时器
    showTime(); 	// 初始时间显示
    resize(150, 60);	// 设置电子时钟显示的尺寸
    showColon = true;	// 初始化
}

// 电子时钟的显示功能
void DigiClock::showTime()
{
    QTime time = QTime::currentTime(); // 获取当前系统时间，保存在 QTime 对象中
    QString text = time.toString("hh:mm");
    if (showColon) {
        text[2] = ':';
        showColon = false;
    } else {
        text[2] = ' ';
        showColon = true;
    }
    display(text);
}

// 鼠标左键点击保存偏移量，右键点击退出窗体
void DigiClock::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) { // event->button() 返回当前鼠标的状态
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    } else if (event->button() == Qt::RightButton) {
        close();
    }
}

// 实现鼠标在桌面上随意拖拽电子时钟的效果
void DigiClock::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}
