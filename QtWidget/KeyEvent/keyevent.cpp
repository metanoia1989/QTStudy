#include "keyevent.h"
#include <QPainter>

KeyEvent::KeyEvent(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("键盘事件"));
    setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::white);
    setPalette(palette);
    setMinimumSize(512, 256);
    setMaximumSize(512, 256);

    width = size().width();
    height = size().height();
    pix = new QPixmap(width, height);
    pix->fill(Qt::white);
//    image.load("image.png");
    image.load("./image.png");
    startX = 100;
    startY = 100;
    step = 20;
    drawPix();
    resize(512, 256);
}

KeyEvent::~KeyEvent()
{

}

// 在 QPixmap对象上绘制图像
void KeyEvent::drawPix()
{
    pix->fill(Qt::white);	// 重新刷新pix对象为白色底色
    QPainter *painter = new QPainter;
    QPen pen(Qt::DotLine);	// 创建QPen对象，画笔的线型为Qt::DotLine 用于绘制网格
    for (int i=step;i<width;i=i+step) {	// 按照步进值的间隔绘制纵向的网格线
        painter->begin(pix); 	// 指定 pix 为绘图设备
        painter->setPen(pen);
        painter->drawLine(QPoint(i, 0), QPoint(i, height));
        painter->end();
    }
    for (int j=step;j<height;j=j+step) {	// 按照步进值的间隔绘制横向的网格线
        painter->begin(pix);
        painter->setPen(pen);
        painter->drawLine(QPoint(0, j), QPoint(width, j));
        painter->end();
    }
    painter->begin(pix);
    painter->drawImage(QPoint(startX, startY), image);	// 绘制可移动的小图标
    painter->end();
}

// 处理键盘的按下事件
void KeyEvent::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier) {	// 判断修饰键Ctrl是否按下
        if (event->key() == Qt::Key_Left) {
            startX = (startX - 1 < 0) ? startX : startX - 1;
        }
        if (event->key() == Qt::Key_Right) {
            startX = (startX + 1 + image.width() > width) ? startX : startX + 1;
        }
        if (event->key() == Qt::Key_Up) {
            startY = (startY - 1 < 0) ? startY : startY - 1;
        }
        if (event->key() == Qt::Key_Down) {
            startY = (startY + 1 + image.height() > height) ? startY : startY + 1;
        }
    } else {	// 对Ctrl键没有按下的处理
        /* 首先调节图标左上顶点的位置至网格的顶点上 */
        startX = startX - startX % step;
        startY = startY - startY % step;
        if (event->key() == Qt::Key_Left) {
            startX = (startX - step < 0) ? startX : startX - step;
        }
        if (event->key() == Qt::Key_Right) {
            startX = (startX + step + image.width() > width) ? startX : startX + step;
        }
        if (event->key() == Qt::Key_Up) {
            startY = (startY - step < 0) ? startY : startY - step;
        }
        if (event->key() == Qt::Key_Down) {
            startY = (startY + step + image.height() > height) ? startY : startY + step;
        }
        if (event->key() == Qt::Key_Home) {	// 恢复图标位置为界面的左上顶点
            startX = 0;
            startY = 0;
        }
        if (event->key() == Qt::Key_End) {	// 将图标位置设为界面的右下顶点
            startX = width - image.width();
            startY = height - image.height();
        }
    }
    drawPix();	// 根据调整后的图标位置重新在 pix 中绘制图像
    update();	// 触发界面重绘
}

void KeyEvent::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(QPoint(0, 0), *pix);
    painter.end();
}
