#include "customer.h"

Customer::Customer(const QString& name, QObject *parent) : QObject(parent)
{
    setObjectName(name);
}

QTextStream& operator<< (QTextStream& os, const Customer& c)
{
    os << c.toString();
    return os;
}
