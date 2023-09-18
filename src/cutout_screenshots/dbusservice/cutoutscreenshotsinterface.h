// Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CUTOUTSCREENSHOTSINTERFACE_H
#define CUTOUTSCREENSHOTSINTERFACE_H

#include <QtDBus/QtDBus>
#include <QImage>

class CutoutScreenShotsInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    {
        return "com.deepin.CutoutScreenShots";
    }

public:
    /**
    * @param: serviceName QDBusConnection 注册的服务名字
    * @param: ObjectPath QDBusConnection 注册的对象路径
    */
    CutoutScreenShotsInterface(const QString &serviceName, const QString &ObjectPath,
                            const QDBusConnection &connection, QObject *parent = nullptr);
    QDBusConnection dbus = QDBusConnection::sessionBus();
    ~CutoutScreenShotsInterface();

public Q_SLOTS: // METHODS
    /**
    * @bref:openFile 通过路径打开图片文件
    * @param: filePath 图片的路径
    * @return: QDBusPendingReply
    */
    inline QDBusPendingReply<> openFile(const QString &filePath)
    {
        qDebug() << "CutoutScreenShotsInterface: " << __FUNCTION__;
        return call(QStringLiteral("openFile"), filePath);
    }
    /**
    * @bref:openImages
    * @param: image 图片
    * @return: QDBusPendingReply
    * @note:
    */
    inline QDBusPendingReply<> openImage(const QImage &image)
    {
        qDebug() << "CutoutScreenShotsInterface: "  << __FUNCTION__;
        QByteArray data;
        QBuffer buf(&data);
        if (image.save(&buf, "PNG")) {
            data = qCompress(data, 9);
            data = data.toBase64();
        }
        return call(QStringLiteral("openImage"), QVariant::fromValue(data));
    }

    /*
    * @bref:openImageAndName
    * @param: image 图片
    * @param: imageName 图片名称
    * @return: QDBusPendingReply
    * @note:
    */
    inline QDBusPendingReply<> openImageAndName(const QImage &image, const QString &imageName, const QPoint &point)
    {
        qDebug() << "CutoutScreenShotsInterface: "  << __FUNCTION__;
        QByteArray data;
        QBuffer buf(&data);
        if (image.save(&buf, "PNG")) {
            data = qCompress(data, 9);
            data = data.toBase64();
        }
        return call(QStringLiteral("openImageAndName"), QVariant::fromValue(data), imageName, point);
    }

Q_SIGNALS: // SIGNALS
};
namespace com {
namespace deepin {
typedef ::CutoutScreenShotsInterface CutoutScreenShots;
}
}
#endif // CUTOUTSCREENSHOTSINTERFACE_H
