#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QObject>
#include <QTextStream>

class Customer : public QObject
{
    Q_OBJECT
public:
    explicit Customer(const QString& name, QObject *parent = nullptr);
    QString toString() const
    {
        QString retval = QString(" Customer: ") + objectName();
        return retval;
    }
};

QTextStream& operator<<(QTextStream& os, const Customer& c);

#endif // CUSTOMER_H
