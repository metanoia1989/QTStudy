#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QString>

class Person : public QObject
{
    Q_OBJECT
public:
    explicit Person(QString name, QObject *parent = nullptr);
    virtual ~Person();

signals:

};

#endif // PERSON_H
