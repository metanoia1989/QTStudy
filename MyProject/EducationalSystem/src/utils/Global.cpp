#include "global.h"
#include "cache.h"


USERINFO::USERINFO(const USERINFO& info)
{
    strToken = info.strToken;
    strDisplayName = info.strDisplayName; // field: name
    strUsername = info.strUsername; // field: username
}

static QSettings* g_settings = nullptr;
static QSettings* g_globalSettings = nullptr;
static Cache* g_cache = nullptr;

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



