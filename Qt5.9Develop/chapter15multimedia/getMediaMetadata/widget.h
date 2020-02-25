#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void selectMediaFile();
    void onMediaStatusChanged(QMediaPlayer::MediaStatus);

private:
    void getMetaData();
    QMediaPlayer *m_player;
};
#endif // WIDGET_H
