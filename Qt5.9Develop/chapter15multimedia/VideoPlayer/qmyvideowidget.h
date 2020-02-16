#ifndef QMYVIDEOWIDGET_H
#define QMYVIDEOWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVideoWidget>
#include <QMediaPlayer>

class QmyVideoWidget : public QVideoWidget
{
public:
    QmyVideoWidget(QWidget *parent=nullptr);
    void setMediaPlayer(QMediaPlayer *palyer);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QMediaPlayer *thePalyer;

};

#endif // QMYVIDEOWIDGET_H
