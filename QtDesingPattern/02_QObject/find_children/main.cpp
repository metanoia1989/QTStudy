#include <QCoreApplication>
#include <QList>
#include <QDebug>
#include "customer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QObject parent;

    Customer *cust1 = new Customer("joe");
    cust1->setParent(&parent);

    Customer *cust2 = new Customer("bil");
    cust2->setParent(&parent);

    QObject* anotherObject = new QObject();
    anotherObject->setObjectName("Junk");
    anotherObject->setParent(&parent);

    // Filter on Customer
    QList<Customer*> custList = parent.findChildren<Customer*>();
    for (const Customer* current : custList) {
        qDebug() << current->toString();
    }

    qDebug() << "Showing all children" << endl;

    QObjectList allChildren = parent.children();
    QObjectList::const_iterator citr;
    for (citr = allChildren.constBegin(); citr != allChildren.constEnd(); ++citr)
    {
        qDebug() << (*citr)->objectName();
    }

    return a.exec();
}
