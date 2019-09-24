#include <QCoreApplication>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // 设置中文显示
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // 建立数据库连接
    db.setHostName("easybook-3313b0");	// 设置数据库主机名
    db.setDatabaseName("qtDB.db");	// 数据库命名
    db.setUserName("smithadam");
    db.setPassword("123456");
    db.open();

    // 创建数据库表
    QSqlQuery query;
    bool success = query.exec("create table automobile ("
        "id int primary key, arrtibute varchar,"
        "type varchar, kind varchar, nation int,"
        "carnumber int, elevaltor int, distance int,"
        "oil int, temperature int)");
    if (success) {
        qDebug() << QObject::tr("数据库表创建成功！\n");
    } else {
        qDebug() << QObject::tr("数据库表创建失败！\n");
    }

    // 查询
    query.exec("select * from automobile");
    QSqlRecord rec = query.record();
    qDebug() << QObject::tr("automobile 表字段数：") << rec.count();

    // 插入记录
    QTime t;
    t.start();	// 启动一个计时器，统计操作耗时
    query.prepare("insert into automobile values(?,?,?,?,?,?,?,?,?,?)");
    long records = 100; // 插值绑定 ODBC 类型定位占位符
    for (int i=0;i<records;i++) {
        query.bindValue(0, i);
        query.bindValue(1, "四轮");
        query.bindValue(2, "轿车");
        query.bindValue(3, "富康");
        query.bindValue(4, rand() % 100);
        query.bindValue(5, rand() % 10000);
        query.bindValue(6, rand() % 300);
        query.bindValue(7, rand() % 20000);
        query.bindValue(8, rand() % 52);
        query.bindValue(9, rand() % 100);
        success = query.exec();
        if (!success) {
            QSqlError lastError = query.lastError();
            qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
        }
    }
    qDebug() << QObject::tr("插入 %1 条记录，耗时：%2ms").arg(records).arg(t.elapsed());

    // 排序
    t.restart();
    success = query.exec("select * from automobile order by id desc");
    if (success) {
        qDebug() << QObject::tr("排序 %1 条记录， 耗时%2ms").arg(records).arg(t.elapsed());
    } else {
        qDebug() << QObject::tr("排序失败！");
    }

    // 更新记录
    t.restart();
    for (int i=0;i<records;i++) {
        query.clear();
        query.prepare(QString("update automobile set attribute=?, type=?,"
            "kind=?, nation=?, carnumber=?, elevaltor=?, distance=?,"
            "oil=?, temperature=? where id=%1").arg(i));
        query.bindValue(0, "四轮");
        query.bindValue(1, "轿车");
        query.bindValue(2, "富康");
        query.bindValue(3, rand() % 100);
        query.bindValue(4, rand() % 10000);
        query.bindValue(5, rand() % 300);
        query.bindValue(6, rand() % 20000);
        query.bindValue(7, rand() % 52);
        query.bindValue(8, rand() % 100);
        success = query.exec();
        if (!success) {
            QSqlError lastError = query.lastError();
            qDebug() << lastError.driverText() << QString(QObject::tr("更新失败"));
        }
    }
    qDebug() << QObject::tr("跟新 %1 条记录，耗时：%2ms").arg(records).arg(t.elapsed());

    // 删除
    t.restart();
    query.exec("delete from automobile where id = 15");
    qDebug() << QObject::tr("删除一条记录，耗时：%1ms").arg(t.elapsed());
    return 0;

//    return a.exec();
}
