#ifndef YSCLOCKPLUGIN_PLUGIN_H
#define YSCLOCKPLUGIN_PLUGIN_H

#include <QQmlExtensionPlugin>

class YSClockPluginPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // YSCLOCKPLUGIN_PLUGIN_H

