#ifndef CACHE_H
#define CACHE_H

#include <QObject>

class Sqlite;

class Cache : public QObject
{
    Q_OBJECT
public:
    explicit Cache(Sqlite *db, QObject *parent = nullptr);

    QString getItem(QString key);
    void setItem(QString key, QString value);
    void removeItem(QString key);
    void clear();

private:
    Sqlite *m_db;
    QString m_tablename;
};

#endif // CACHE_H
