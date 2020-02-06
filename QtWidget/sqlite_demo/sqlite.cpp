#include "sqlite.h"

Sqlite::Sqlite()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}


bool Sqlite::sqlite_connect()
{
    db.setDatabaseName("");
    return false;
}
