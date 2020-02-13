#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QObject>

class DataObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)

public:
    explicit DataObject(const QString &name, const QString &color,
                        QObject *parent = nullptr);
    void setName(const QString &name);
    QString name() const;

    void setColor(const QString &color);
    QString color() const;

signals:
    void nameChanged(const QString &name);
    void colorChanged(const QString &color);

private:
    QString mName;
    QString mColor;
};

#endif // DATAOBJECT_H
