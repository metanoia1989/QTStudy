#include "MandelbrotCalculator.h"
#include "Job.h"

#include <QThreadPool>
#include <QDebug>

const int JOB_RESULT_THREASHOLD = 10;

MandelbrotCalculator::MandelbrotCalculator(QObject *parent) :
    QObject(parent),
    mMoveOffset(0.0, 0.0),
    mScaleFactor(0.005),
    mAreaSize(0, 0),
    mIterationMax(10),
    mReceivedJobResult(0),
    mJobResults(),
    mTimer()
{

}
