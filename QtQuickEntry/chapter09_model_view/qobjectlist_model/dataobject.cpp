#include "dataobject.h"

DataObject::DataObject(const QString &name, const QString &color,
    QObject *parent) : QObject(parent), mName(name),mColor(color)
{

}

void DataObject::setName(const QString &name)
{
    mName = name;
    emit nameChanged(name);
}

QString DataObject::name() const
{
    return mName;
}

void DataObject::setColor(const QString &color)
{
    mColor = color;
    emit colorChanged(color);
}

QString DataObject::color() const
{
    return mColor;
}
