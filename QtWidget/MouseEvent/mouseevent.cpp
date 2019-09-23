#include "mouseevent.h"

MouseEvent::MouseEvent(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("鼠标事件"));
    statusLabel = new QLabel;	 // 用于显示鼠标移动时的实时位置
    statusLabel->setText(tr("当前位置："));
    statusLabel->setFixedWidth(100);
    MousePosLabel = new QLabel;	//  用于显示鼠标键按下或释放的位置
    MousePosLabel->setText(tr(""));
    MousePosLabel->setFixedWidth(100);
    statusBar()->addPermanentWidget(statusLabel);	// 状态栏新增控件
    statusBar()->addPermanentWidget(MousePosLabel);
    this->setMouseTracking(true);	// 设置窗体追踪鼠标
    resize(400, 200);
}

MouseEvent::~MouseEvent()
{

}

void MouseEvent::mousePressEvent(QMouseEvent *e)
{
    // 获取鼠标相对于接收事件的窗体位置
    QString str = "(" + QString::number(e->x()) + "," + QString::number(e->y()) + ")";
    if (e->button() == Qt::LeftButton) {
        statusBar()->showMessage(tr("左键：") + str);
    } else if (e->button() == Qt::RightButton) {
        statusBar()->showMessage(tr("左键：") + str);
    } else if (e->button() == Qt::MidButton) {
        statusBar()->showMessage(tr("中键：") + str);
    }
}

void MouseEvent::mouseMoveEvent(QMouseEvent *e)
{
    QString str = "(" + QString::number(e->x()) + "," + QString::number(e->y()) + ")";
    MousePosLabel->setText(str);
}

void MouseEvent::mouseReleaseEvent(QMouseEvent *e)
{
    QString str = "(" + QString::number(e->x()) + "," + QString::number(e->y()) + ")";
    statusBar()->showMessage(tr("释放在：") + str);
}


void MouseEvent::mouseDoubleClickEvent(QMoveEvent *e) { }
