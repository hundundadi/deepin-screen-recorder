// Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DBUSCUTOUTSCREENSHOTSADAPTOR_H
#define DBUSCUTOUTSCREENSHOTSADAPTOR_H
#include <QtCore/QObject>
#include <QtDBus/QtDBus>
QT_BEGIN_NAMESPACE
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE
/**
 * @brief  提供给外部程序调用的方法
 */
class DbusCutoutScreenShotsAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    //类的附加信息 可以为类的元对象定义“名称--值”
    Q_CLASSINFO("D-Bus Interface", "com.deepin.CutoutScreenShots")
    Q_CLASSINFO("D-Bus Introspection", ""
                "  <interface name=\"com.deepin.CutoutScreenShots\">\n"

                "    <method name=\"openImage\">\n"
                "      <arg direction=\"in\" type=\"ay\" name=\"openImage\"/>\n"
                "    </method>\n"

                "    <method name=\"openImageAndName\">\n"
                "      <arg direction=\"in\" type=\"ay\" name=\"images\"/>\n"
                "      <arg direction=\"in\" type=\"s\" name=\"imageName\"/>\n"
                "    </method>\n"

                "    <method name=\"openFile\">\n"
                "      <arg direction=\"in\" type=\"s\" name=\"openFile\"/>\n"
                "      <arg direction=\"out\" type=\"b\"/>\n"
                "    </method>\n"

                "  </interface>\n")

public:
    explicit DbusCutoutScreenShotsAdaptor(QObject *parent);
    virtual ~DbusCutoutScreenShotsAdaptor();

public Q_SLOTS: // METHODS
    void openImage(QByteArray images);
    void openImageAndName(QByteArray images, QString imageName, QPoint point);
    bool openFile(QString filePath);

Q_SIGNALS: // SIGNALS

};

#endif // DBUSPINSCREENSHOTSADAPTOR_H
