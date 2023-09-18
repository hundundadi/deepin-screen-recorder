QT += core gui
QT += dtkgui dtkwidget dbus
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = deepin-cutout-screenshots
TEMPLATE = app
CONFIG += c++11 link_pkgconfig
PKGCONFIG += dtkwidget

SOURCES += \
    main.cpp \
    cutoutscreenshots.cpp \
    dbusservice/cutoutscreenshotsinterface.cpp \
    dbusservice/dbuscutoutscreenshotsadaptor.cpp \
    ui/mainwindow.cpp \
    ui/leftwidget.cpp \
    ui/rightwidget.cpp

RESOURCES +=         resources.qrc

HEADERS += \
    cutoutscreenshots.h \
    dbusservice/cutoutscreenshotsinterface.h \
    dbusservice/dbuscutoutscreenshotsadaptor.h \
    ui/mainwindow.h \
    ui/leftwidget.h \
    ui/rightwidget.h

##安装路径
target.path=/usr/bin
isEmpty(DSRDIR):DSRDIR=/usr/share/deepin-cutout-screenshots

#Dbus文件
dbus_service.path=/usr/share/dbus-1/services
dbus_service.files=./com.deepin.CutoutScreenShots.service

#安装
INSTALLS += target dbus_service
