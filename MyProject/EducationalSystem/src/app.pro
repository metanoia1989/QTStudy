
QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE = app

SOURCES += \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    studentitemmodel.cpp \
    share/WizWin32Helper.cpp

HEADERS += \
    logindialog.h \
    mainwindow.h \
    studentitemmodel.h \
    share/WizWin32Helper.h

FORMS += \
    logindialog.ui \
    mainwindow.ui

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
