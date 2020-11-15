#pragma once

#include <QObject>
#include <QSize>
#include <QPointF>
#include <QElapsedTimer>
#include <QList>

#include "JobResult.h"

class Job;

class MandelbrotCalculator : public QObject
{
    Q_OBJECT
public:
    explicit MandelbrotCalculator(QObject *parent = nullptr);
    void init(QSize imageSize);

signals:
    // 定期触发调度结果
    void pictureLinesGenerated(QList<JobResult> jobResults);
    // 终止所有活动的任务
    void abortAllJobs();

public slots:
    // 请求一个新的霍夫曼图片时调用，准备并开启任务
    void generatePicture(QSize areaSize, QPointF moveOffset,
                         double scaleFactor, int iterationMax);
    // 处理任务计算的结果
    void process(JobResult jobResult);

private:
    Job* createJob(int pixelPositionY);
    void clearJobs();

    QPointF mMoveOffset;
    double mScaleFactor;
    QSize mAreaSize;
    int mIterationMax;
    int mReceivedJobResult; // 接收JobResult的计数
    QList<JobResult> mJobResults; // 存储JobResult的容器
    QElapsedTimer mTimer; // 计算运行所有作业的时间

};

