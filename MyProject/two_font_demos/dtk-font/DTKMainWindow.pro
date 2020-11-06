QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += link_pkgconfig
PKGCONFIG += dtkwidget

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += /usr/include/libdtk-5.2.1/DGui
INCLUDEPATH += /usr/include/libdtk-5.2.2/DCore
INCLUDEPATH += /usr/include/libdtk-5.2.2/DWidget

SOURCES += \
    main.cpp \
    dtkmainwindow.cpp

HEADERS += \
    dtkmainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    resource.qrc