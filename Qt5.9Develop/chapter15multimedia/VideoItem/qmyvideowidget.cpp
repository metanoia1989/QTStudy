#include "qmyvideowidget.h"
#include <QKeyEvent>
#include <QMouseEvent>

QmyVideoWidget::QmyVideoWidget(QWidget *parent) :QVideoWidget(parent)
{

}

// 设置播放器
void QmyVideoWidget::setMediaPlayer(QMediaPlayer *palyer)
{
    thePalyer = palyer;
}


// 按键事件，ESC退出全屏状态
void QmyVideoWidget::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() == Qt::Key_Escape) && isFullScreen()) {
        setFullScreen(false);
        event->accept();
        QVideoWidget::keyPressEvent(event);
    }
}

// 鼠标事件，单击控制暂停和继续播放
void QmyVideoWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (thePalyer->state() == QMediaPlayer::PlayingState) {
            thePalyer->pause();
        } else {
            thePalyer->play();
        }
    }
    QVideoWidget::mousePressEvent(event);
}
