#ifndef GLOBAL_H
#define GLOBAL_H

#include <QMetaType>
#include <QMap>
#include <QSettings>
#include <QDateTime>
#include "cache.h"

/**
 * 重写QDatetime类，添加一些好用方便的接口
 */
class DateTime: public QDateTime
{
public:
    DateTime() :QDateTime() { *this = QDateTime::currentDateTime(); }
    DateTime(const QDateTime& other) { *this = other; }
    DateTime(int year, int month, int day, int hour, int minute, int second) : QDateTime(QDate(year, month, day), QTime(hour, minute, second))  {}
    DateTime(time_t t) { this->setTime_t(t);}

    int getYear() const { return date().year(); }
    int getMonth() const { return date().month(); }
    int getDay() const { return date().day(); }
    int getHour() const { return time().hour(); }
    int getMinute() const { return time().minute(); }
    int getSecond() const { return time().second(); }
    int getDayOfYear() const { return date().dayOfYear(); }
    int getDayOfWeek() const { return date().dayOfWeek(); }

    QString toHumanFriendlyString() const;
    QString toLocalLongDate() const;

    DateTime &operator=(const QDateTime &other);
    DateTime &operator=(const DateTime &other);
};

/**
 * @brief 用户信息结构体
 */
struct USERINFO 
{
    USERINFO() {};
    USERINFO(const USERINFO& info);

    QString strToken;
    QString strUsername; // field: username
    DateTime tTokenExpried;
};

Q_DECLARE_METATYPE(USERINFO)

/**
 * 单例模式管理类   
 */
class Cache;
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


/**
 * @brief 获取服务器地址
 * @return
 */
QString getServerUrl();

/**
 * @brief 展示错误信息
 */
void showErrorMsg();

#endif // GLOBAL_H
