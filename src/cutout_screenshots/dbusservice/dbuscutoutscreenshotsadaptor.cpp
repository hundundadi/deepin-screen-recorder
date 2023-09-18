// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "dbuscutoutscreenshotsadaptor.h"
#include <QtCore/QMetaObject>
#include <QImage>
DbusCutoutScreenShotsAdaptor::DbusCutoutScreenShotsAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

DbusCutoutScreenShotsAdaptor::~DbusCutoutScreenShotsAdaptor()
{
    // destructor
}

bool DbusCutoutScreenShotsAdaptor::openFile(QString filePath)
{
    qDebug() << __FUNCTION__ << __LINE__;
    QMetaObject::invokeMethod(parent(), "openFile", Q_ARG(QString, filePath));
    return true;
}


void DbusCutoutScreenShotsAdaptor::openImageAndName(QByteArray images, QString imageName, QPoint point)
{
    qDebug() << __FUNCTION__ << __LINE__;
    QByteArray data = images;
    QString tmp_data = QString::fromLatin1(data.data(), data.size());
    QByteArray srcData = QByteArray::fromBase64(tmp_data.toLatin1());
    data = qUncompress(srcData);
    QImage image;
    image.loadFromData(data);
    QMetaObject::invokeMethod(parent(), "openImageAndName", Q_ARG(QImage, image), Q_ARG(QString, imageName), Q_ARG(QPoint, point));
}

void DbusCutoutScreenShotsAdaptor::openImage(QByteArray images)
{
    qDebug() << __FUNCTION__ << __LINE__;
    QByteArray data = images;
    QString tmp_data = QString::fromLatin1(data.data(), data.size());
    QByteArray srcData = QByteArray::fromBase64(tmp_data.toLatin1());
    data = qUncompress(srcData);
    QImage image;
    image.loadFromData(data);
    QMetaObject::invokeMethod(parent(), "openImage", Q_ARG(QImage, image));
}
