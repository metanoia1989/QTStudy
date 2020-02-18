#include <QDebug>
#include <QtCore>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    QTextStream cout(stdout, QIODevice::WriteOnly);
    /* 字符串操作 */
    cout << QString("字符串操作：\n");
    QString s1{"Paris"};
    QString s2{"London"};
    QString s = s1 + " " + s2 + "!";
    cout << s << endl;

    /* 容器类操作 */
    cout << QString("容器类输出：\n");
    QString s3("Hello");
    QString s4("Qt");
    QList<QString> list;
    // 流入容器
    list << s3 << s4;

    // Java和STL风格迭代器
    QListIterator<QString> iter(list);
    while(iter.hasNext()) {
        cout << iter.next();
        if (iter.hasNext()) {
            cout << " ";
        }
    }
    cout << "!" << endl;

    /* 容器连接为字符串 */
    cout << QString("容器连接字符串:\n");
    s = list.join("+") + "!";
    cout << s << endl;

    /* 文件读写操作 */
    QList<QStringList> data;
    QFile file("sample.csv");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        // loop forevet macro
        forever {
            QString line = stream.readLine();
            if (line.isNull()) break;
            if (line.isEmpty()) continue;
            QStringList row;
            // 对于每个循环遍历容器
            foreach(const QString& cell, line.split(",")) {
                row.append(cell.trimmed());
            }
            data.append(row);
        }
    }
    cout << QString("有多少条数据：") << data.length() << endl;

//    QSqlDatabase db1 = QSqlDatabase::addDatabase("QSQLITE", "conn1");
//    db1.setDatabaseName("test.sqlite");
//    if (db1.open()) {
//        qDebug() << "db1 open";
//        QSqlQuery query("CREATE TABLE test1 (a integer)", db1);
//        qDebug() << "Tables in db1" << db1.tables();
//    } else {
//        qDebug() << "打开失败";
//    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
    db.setDatabaseName("test.sqlite");
    if (!db.open()) {
       qDebug() << "打开失败";
    } else {
        qDebug() << "打开成功";
//        QSqlQuery query;
         QSqlQuery query("SELECT * FROM test1", db);
        if(!query.exec()) {
            qDebug() << query.lastError();
        } else {
            qDebug() << "查询成功";
        }
    }

}
