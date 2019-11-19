#ifndef QPERSON_H
#define QPERSON_H

#include <QObject>

class QPerson : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("author", "Smith")
    Q_CLASSINFO("company", "WWW")
    Q_CLASSINFO("version", "1.0.0")

    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(QString name MEMBER mName)
    Q_PROPERTY(int score MEMBER mScore)

public:
    explicit QPerson(QString fName, QObject *parent = nullptr);
    int age();
    void setAge(int value);
    void incAge();

signals:
    void ageChanged(int value);

public slots:

private:
    int mAge = 10;
    QString mName;
    int mScore = 79;
};

#endif // QPERSON_H
