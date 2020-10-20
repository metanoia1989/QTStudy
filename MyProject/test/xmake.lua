add_rules("mode.debug", "mode.release")

target("test")
    add_rules("qt.console")
    add_files("src/*.cpp")
    add_frameworks("QtNetwork")