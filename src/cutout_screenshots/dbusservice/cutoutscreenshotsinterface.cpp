// Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "cutoutscreenshotsinterface.h"

CutoutScreenShotsInterface::CutoutScreenShotsInterface(const QString &serviceName,
                                                 const QString &ObjectPath,
                                                 const QDBusConnection &connection,
                                                 QObject *parent)
    : QDBusAbstractInterface(serviceName, ObjectPath, staticInterfaceName(), connection, parent)

{

}

CutoutScreenShotsInterface::~CutoutScreenShotsInterface()
{

}
