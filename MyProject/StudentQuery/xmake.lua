add_rules("mode.debug", "mode.release")

includes("qt_add_static_plugins.lua")

target("StudentQuery")
    add_rules("qt.widgetapp_static")
    add_rules("qt.qrc") 
    add_headerfiles("src/*.h")
    add_files("src/*.cpp")
    add_frameworks("QtWidgets", "QtNetwork")
    -- add files with Q_OBJECT meta (only for qt.moc)
    add_files("src/widget.h")
    add_files("src/resource.qrc")
    add_files("src/app_win32.rc")

    -- add plugin: QSvgPlugin (optional)
    -- qt_add_static_plugins("QSvgPlugin", {linkdirs = "plugins/imageformats", links = {"qsvg", "Qt5Svg"}})
