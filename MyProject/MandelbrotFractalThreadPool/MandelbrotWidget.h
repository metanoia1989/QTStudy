#pragma once

#include <memory>
#include <QWidget>
#include <QPoint>
#include <QThread>
#include <QList>

#include "MandelbrotCalculator.h"

class QResizeEvent;

class MandelbrotWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MandelbrotWidget(QWidget *parent = nullptr);
    ~MandelbrotWidget();

public slots:
    // 处理任务结果
    void processJobResults(QList<JobResult> jobResults);

signals:
    // 用户改变输入数据 offset scale areaSize
    void requestPicture(QSize areaSize, QPointF moveOffset, double scaleFactor, int iterationMax);

protected:
    void paintEvent(QPaintEvent *event) override; // 绘制当前图片宽度
    void resizeEvent(QResizeEvent *event) override; // 改变视区大小
    void wheelEvent(QWheelEvent *event) override; // 鼠标滚动事件
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override; // 鼠标移动事件

private:
    QRgb generateColorFromIteration(int iteration); // 按像素的迭代值生成颜色

    MandelbrotCalculator mMandelbrotCalculator; // 工作任务管理线程
    QThread mThreadCalculator; // 计算主线程
    double mScaleFactor;
    QPoint mLastMouseMovePosition; // 用户鼠标移动的位置
    QPointF mMoveOffset;
    QSize mAreaSize;
    int mIterationMax;
    std::unique_ptr<QImage> mImage; // 展示当前图片
};
