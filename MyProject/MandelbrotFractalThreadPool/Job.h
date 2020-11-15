#pragma once

#include <QObject>
#include <QRunnable>
#include <QPointF>
#include <QSize>
#include <QAtomicInteger>

class JobResult;

class Job : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Job(QObject *parent = nullptr);
    void run() override;

    void setPixelPositionY(int value);
    void setMoveOffset(const QPointF& value);
    void setScaleFactor(double value);
    void setAreaSize(const QSize& value);
    void setIterationMax(int value);

signals:
    void jobCompleted(JobResult jobResult); // 计算结束的信号

public slots:
    void abort();

private:
    int mPixelPositionY; // 照片高度
    QPointF mMoveOffset; // 控件偏移
    double mScaleFactor; // 缩放大小
    QSize mAreaSize; // 照片大小
    int mIterationMax; // 最大的迭代次数
    QAtomicInteger<bool> mAbort; // 任务终止
};

