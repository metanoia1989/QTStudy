#ifndef GLOBAL_H
#define GLOBAL_H

#include <QMetaType>
#include <QImage>
#include <QMap>
#include <QSettings>

class Cache;

struct USERINFO 
{
    USERINFO();
    USERINFO(const USERINFO& info);

    QString strToken;
    QString strDisplayName; // field: name
    QString strUsername; // field: username
};

Q_DECLARE_METATYPE(USERINFO)

/**
 * 单例模式管理类   
 */
class Global : public QObject
{
    Q_OBJECT

private:
    explicit Global();
public:
    ~Global();

public:
    static Global* instance();

    static void setSettings(QSettings *settings);
    static QSettings *settings();
    static void setGlobalSettings(QSettings *settings);
    static QSettings *globalSettings();
    static void setCache(Cache *cache_class);
    static Cache *cache();
};


#endif // GLOBAL_H
