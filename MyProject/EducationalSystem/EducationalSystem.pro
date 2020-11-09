TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = third-party/QtNetworkService \
    src/app.pro
    
app.depends = third-party/QtNetworkService


