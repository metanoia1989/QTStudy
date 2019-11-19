#include "qperson.h"

QPerson::QPerson(QString fName, QObject *parent) : QObject(parent)
{
    mName = fName;
}

int QPerson::age()
{
    return mAge;
}

// 设置 age
void QPerson::setAge(int value)
{
    mAge = value;
    emit ageChanged(mAge);	// 发射信号
}

void QPerson::incAge()
{
    mAge++;
    emit ageChanged(mAge);	// 发射信号
}
