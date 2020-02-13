#include "backend.h"

BackEnd::BackEnd(QObject *parent) : QObject(parent)
{

}

QString BackEnd::userName()
{
    return mUserName;
}

void BackEnd::setUserName(const QString &userName)
{
    if (userName == mUserName) {
        return;
    }
    mUserName = userName;
    emit userNameChanged();
}
