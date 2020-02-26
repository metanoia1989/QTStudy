#include "qwbattery.h"
#include "qwbatteryplugin.h"

#include <QtPlugin>

QwBatteryPlugin::QwBatteryPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void QwBatteryPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QwBatteryPlugin::isInitialized() const
{
    return m_initialized;
}

// 返回自定义的Widget组件的实例
QWidget *QwBatteryPlugin::createWidget(QWidget *parent)
{
    return new QwBattery(parent);
}

// 自定义Widget组件类的名称
QString QwBatteryPlugin::name() const
{
    return QLatin1String("QwBattery");
}

// 在组件面板中所属分组名称
QString QwBatteryPlugin::group() const
{
    return QLatin1String("");
}

// 组件的图标
QIcon QwBatteryPlugin::icon() const
{
    return QIcon(QLatin1String(":/44.ico"));
}

// toolTip信息
QString QwBatteryPlugin::toolTip() const
{
    return QLatin1String("Battery charger indicator");
}

// whatsThis 信息
QString QwBatteryPlugin::whatsThis() const
{
    return QLatin1String("A battery charger indicator");
}

// 设置组件是否作为容器
bool QwBatteryPlugin::isContainer() const
{
    return false;
}

// 用XML设置组件的一些属性
QString QwBatteryPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QwBattery\" name=\"qwBattery\">\n</widget>\n");
}

// 包含的头文件
QString QwBatteryPlugin::includeFile() const
{
    return QLatin1String("qwbattery.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qwbatteryplugin, QwBatteryPlugin)
#endif // QT_VERSION < 0x050000
