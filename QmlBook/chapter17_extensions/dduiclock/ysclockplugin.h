#ifndef YSCLOCKPLUGIN_H
#define YSCLOCKPLUGIN_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QTimer>
#include <QTime>

class YSClockPlugin : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor hourColor READ hourColor WRITE setHourColor NOTIFY hourColorChanged)
    Q_PROPERTY(QColor minuteColor READ minuteColor WRITE setMinuteColor NOTIFY minuteColorChanged)
    Q_PROPERTY(QColor secondColor READ secondColor WRITE setSecondColor NOTIFY secondColorChanged)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY backgroundChanged)

    Q_PROPERTY(bool startUpdate READ startUpdate WRITE setStartUpdate NOTIFY startUpdateChanged)
    Q_PROPERTY(QString ysfamily READ ysfamily WRITE setYsfamily NOTIFY ysfamilyChanged)


public:
    YSClockPlugin(QQuickItem *parent = 0);
    ~YSClockPlugin();

    QColor hourColor();
    void setHourColor(QColor color);

    QColor minuteColor();
    void setMinuteColor(QColor color);

    QColor secondColor();
    void setSecondColor(QColor color);

    QColor lineColor();
    void setLineColor(QColor color);

    QColor textColor();
    void setTextColor(QColor color);

    QColor background();
    void setBackground(QColor color);

    bool startUpdate();
    void setStartUpdate(bool start=true);

    QString ysfamily();
    void setYsfamily(QString family="微软雅黑");

    Q_INVOKABLE void setTitle(const QString& title="");
protected:
    void paint(QPainter* p);
signals:
    void hourColorChanged();
    void minuteColorChanged();
    void secondColorChanged();
    void lineColorChanged();
    void textColorChanged();
    void startUpdateChanged();
    void ysfamilyChanged();
    void backgroundChanged();

private:
    QTimer *timer;
    QColor m_huorColor;
    QColor m_minColor;
    QColor m_secColor;
    QColor m_lineColor;
    QColor m_textColor;
    QColor m_background;
    bool  m_start;
    QString m_family;
    QString m_title;
};

#endif // YSCLOCKPLUGIN_H

