#ifndef QMYBATTERY_H
#define QMYBATTERY_H

#include <QWidget>
#include <QColor>

class QmyBattery : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int powerLevel READ powerLevel WRITE setPowerLevel NOTIFY powerLevelChanged)

public:
    explicit QmyBattery(QWidget *parent = nullptr);
    void setPowerLevel(int pow);	// 设置当前电量
    int powerLevel();
    void setWarnLevel(int warn); // 设置电量低阈值
    int warnLevel();
    QSize sizeHint() const override; // 报告缺省大小

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void powerLevelChanged(int powerLevel);

private:
    QColor mColorBack = Qt::white; // 背景颜色
    QColor mColorBorder = Qt::black; // 电池边框颜色
    QColor mColorPower = Qt::green; // 电池柱颜色
    QColor mColorWarning = Qt::red; // 电池短缺时颜色
    int mPowerLevel = 0; // 电量0-100
    int mWarnLevel = 20; // 电量低警示阈值
};

#endif // QMYBATTERY_H
