
QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE = app

SOURCES += \
    logindialog.cpp \
    main.cpp \
    informationlist.cpp \
    studentitemmodel.cpp \
    utils/global.cpp \
    utils/WizWin32Helper.cpp \
    utils/cache.cpp \
    utils/sqlite.cpp \
    utils/threads.cpp \
    utils/token.cpp

HEADERS += \
    logindialog.h \
    informationlist.h \
    studentitemmodel.h \
    utils/global.h \
    utils/WizWin32Helper.h \
    utils/cache.h \
    utils/sqlite.h \
    utils/threads.h \
    utils/threads_p.h \
    utils/token_p.h \
    utils/token.h

FORMS += \
    logindialog.ui \
    informationlist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../assets/resource.qrc

RC_FILE = ../assets/app_win32.rc

CONFIG(release, debug|release) {
    inis.path = $${OUT_PWD}/release/
}
CONFIG(debug, debug|release) {
    inis.path = $${OUT_PWD}/debug/
}
inis.files += ../assets/config.ini
INSTALLS += inis

DEFINES += QT_APP_DEBUG
include(../third-party/QtNetworkService/QtNetworkService.pri)
