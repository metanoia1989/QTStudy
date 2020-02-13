#include <QtSql>
#include <QStringList>
#include <QDebug>

int main()
{
  // create sql database
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setConnectOptions("QSQLITE_OPEN_URI;QSQLITE_ENABLE_SHARED_CACHE");
  db.setDatabaseName("file::memory:"); /* *** */
  qDebug() << "Opening original database: " << db.open();

  // add some tables
  QSqlQuery query;
  query.exec("CREATE TABLE table1 (_id INTEGER PRIMARY KEY)");
  query.exec("CREATE TABLE table2 (_id INTEGER PRIMARY KEY)");

  qDebug() << "Tables in original: " << db.tables();

  // try to clone connection...
  QSqlDatabase clone = QSqlDatabase::cloneDatabase(db, "clone");
  qDebug() << "Opening clone: " << clone.open();
  qDebug() << "Tables in clone: " << clone.tables();

  QtConcurrent::run(this, [&MainWindow](){
      MainWindow::test();
  });

  return 0;
}
