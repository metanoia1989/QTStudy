TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = third-party/QtNetworkService \
    third-party/QSimpleUpdater \
    src/app.pro
    
app.depends = third-party/QtNetworkService
app.depends = third-party/QSimpleUpdater 


