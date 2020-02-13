#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QStringList>
#include <QDebug>

int main2(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QSqlDatabase db1 = QSqlDatabase::addDatabase("QSQLITE", "conn1");
    db1.setDatabaseName(":memory:");
    if (db1.open()) {
        qDebug() << "db1 open";
        QSqlQuery qry("CREATE TABLE test1 (a integer)", db1);
        qDebug() << "Tables in db1" << db1.tables();
    }

    QSqlDatabase db2 = QSqlDatabase::addDatabase("QSQLITE", "conn2");
    db1.setDatabaseName(":memory:");

    if (db2.open()) {
        qDebug() << "db2 open";
        QSqlQuery qry("CREATE TABLE test2 (a integer)", db2);
        qDebug() << "Tables in db2" << db2.tables();
    }

    qDebug() << "重新检测：";
    qDebug() << "db1 open" << db1.isOpen();
    qDebug() << "db2 open" << db2.isOpen();
    qDebug() << "Tables in db1" << db1.tables();
    qDebug() << "Tables in db2" << db2.tables();

    return 0;
}
