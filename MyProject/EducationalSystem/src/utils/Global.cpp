#include "global.h"
#include <QCoreApplication>
#include <QLocale>
#include <QMessageBox>

//****************************************************
// 日期助手类
//****************************************************
QString DateTime::toHumanFriendlyString() const
{
    QDateTime t(QDateTime::currentDateTime());
    int nElapseSecs = secsTo(t);
    int nElapseDays = daysTo(t);

    if (nElapseDays == 1) {
        return QObject::tr("Yesterday");
    } else if (nElapseDays == 2) {
        return QObject::tr("The day before yesterday");
    } else if (nElapseDays > 2) {
        return toString("yyyy/M/d");
    }

    if (nElapseSecs < 60) {
        // less than 1 minutes: "just now"
        return QObject::tr("Just now");

    } else if (nElapseSecs >= 60 && nElapseSecs < 60 * 2) {
        // 1 minute: "1 minute ago"
        return QObject::tr("1 minute ago");

    } else if (nElapseSecs >= 120 && nElapseSecs < 60 * 60) {
        // 2-60 minutes: "x minutes ago"
        QString str = QObject::tr("%1 minutes ago");
        return str.arg(nElapseSecs/60);

    } else if (nElapseSecs >= 60 * 60 && nElapseSecs < 60 * 60 * 2) {
        // 1 hour: "1 hour ago"
        return QObject::tr("1 hour ago");

    } else if (nElapseSecs >= 60 * 60 * 2 && nElapseSecs < 60 * 60 * 24) {
        // 2-24 hours: "x hours ago"
        QString str = QObject::tr("%1 hours ago");
        return str.arg(nElapseSecs/60/60);
    }

    return QString("Error");
}

QString DateTime::toLocalLongDate() const
{
    QLocale local;
    if (local.language() == QLocale::Chinese)
    {
        QDateTime dt = QDateTime::currentDateTime();
        return local.toString(dt, "yyyy") + QObject::tr("year") + local.toString(dt, "MMMd") + QObject::tr("day");
    }

    return QDateTime::currentDateTime().toString("MMM d,yyyy");
}

DateTime &DateTime::operator=(const QDateTime &other)
{
    setDate(other.date());
    setTime(other.time());
    return *this;
}

DateTime &DateTime::operator=(const DateTime &other)
{
    setDate(other.date());
    setTime(other.time());
    return *this;
}


//****************************************************
// 用户信息结构体
//****************************************************
USERINFO::USERINFO(const USERINFO& info)
{
    strToken = info.strToken;
    strUsername = info.strUsername; // field: username
}

static QSettings* g_settings = nullptr;
static QSettings* g_globalSettings = nullptr;
static Cache* g_cache = nullptr;


//****************************************************
// 全局单例管理
//****************************************************
Global::Global()
{
}

Global::~Global()
{
    g_settings = nullptr;
    g_globalSettings = nullptr;
    g_cache = nullptr;
}

Global* Global::instance()
{
    static Global instance;
    return &instance;
}

void Global::setSettings(QSettings *settings)
{
    if (g_settings)
    {
        delete g_settings;
        g_settings = nullptr;
    }

    g_settings = settings;
    g_settings->setParent(Global::instance());
}

QSettings *Global::settings()
{
    return g_settings;
}

void Global::setGlobalSettings(QSettings *settings)
{
    if (g_globalSettings)
    {
        delete g_globalSettings;
        g_globalSettings = nullptr;
    }
    //
    g_globalSettings = settings;
    g_globalSettings->setParent(Global::instance());
}

QSettings *Global::globalSettings()
{
    return g_globalSettings;
}

void Global::setCache(Cache *cache_class)
{
    if (g_cache)
    {
        delete g_cache;
        g_cache = nullptr;
    }
    g_cache = cache_class;
    g_cache->setParent(instance());
}

Cache *Global::cache()
{
    return g_cache;
}



//****************************************************
// 工具类函数
//****************************************************

/**
 * @brief 获取服务器地址
 * @return
 */
QString getServerUrl()
{
    QString iniPath =  QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings settings(iniPath, QSettings::IniFormat);
    settings.beginGroup("Site");
    QString server_url = settings.value("educational_site").toString();
    if (server_url.isEmpty()) {
        return "";
    }
    settings.endGroup();
    return server_url;
}

void showErrorMsg(QString msg)
{
    auto msgBox = new QMessageBox();
    msgBox->setWindowTitle("请求出错");
    msgBox->setIcon(QMessageBox::Critical);
    msgBox->setText(msg);
    msgBox->exec();
    msgBox->deleteLater();
}
