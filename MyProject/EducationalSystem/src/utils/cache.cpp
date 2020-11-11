#include "cache.h"
#include "sqlite.h"

Cache::Cache(Sqlite *db, QObject *parent) :
    QObject(parent)
    , m_db(db)
    , m_tablename("es_cache")
{
    // 检测缓存表是否存在，不存在则创建
    if(!db->hasTable(m_tablename)) {
        db->createTable(m_tablename, "key varchar, value text");
    }
}

QString Cache::getItem(QString key)
{
    QSqlQuery query = m_db->queryRecord(m_tablename, QString("key;'%1'").arg(key));
    query.first();
    QVariant value = query.value("value");
    if (!value.isValid()) {
        return "";
    }
    return value.toString();
}

void Cache::setItem(QString key, QString value)
{
    m_db->delRecord(m_tablename, "key", key);
    m_db->insertRecord(m_tablename, "key, value", QString("'%1','%2'").arg(key).arg(value));
}

void Cache::removeItem(QString key)
{
    m_db->delRecord(m_tablename, "key", key);
}

void Cache::clear()
{
    m_db->clearTable(m_tablename);
}
