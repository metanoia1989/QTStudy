#ifndef SQLITE_H
#define SQLITE_H

#include <QtSql/QSqlDatabase>

class Sqlite
{
public:
    Sqlite();
    static QSqlDatabase db;
    static bool sqlite_connect();
};

#endif // SQLITE_H
