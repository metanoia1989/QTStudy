add_rules("mode.debug", "mode.release")

target("downloadFile")
    add_rules("qt.widgetapp")
    add_headerfiles("*.h")
    add_files("*.cpp")
    -- add files with Q_OBJECT meta (only for qt.moc)
    add_files("main.cpp", {rule="qt.moc"})

    add_frameworks("QtCore", "QtNetwork")