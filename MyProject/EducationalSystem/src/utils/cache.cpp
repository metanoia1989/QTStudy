#include "cache.h"
#include "sqlite.h"

Cache::Cache(Sqlite *db, QObject *parent) :
    QObject(parent)
    , m_db(db)
{
    // 检测缓存表是否存在，不存在则创建
    if(!db->hasTable("es_cache")) {
        db->createTable("es_table", "key varchar, value text");
    }
}

QString Cache::getItem(QString key)
{

}

void Cache::setItem(QString key, QString value)
{

}

void Cache::removeItem(QString key)
{

}

void Cache::clear()
{

}
