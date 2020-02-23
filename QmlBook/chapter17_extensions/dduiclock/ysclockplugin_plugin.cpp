#include "ysclockplugin_plugin.h"
#include "ysclockplugin.h"

#include <qqml.h>

void YSClockPluginPlugin::registerTypes(const char *uri)
{
    // @uri com.ys.qmlcomponents
    qmlRegisterType<YSClockPlugin>(uri, 1, 0, "YSClockPlugin");
}


