// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CUTOUTSCREENSHOTS_H
#define CUTOUTSCREENSHOTS_H

#include <QObject>
#include <QImage>
class CutoutScreenShots : public QObject
{
    Q_OBJECT
public:
    explicit CutoutScreenShots(QObject *parent = nullptr);

    Q_INVOKABLE bool openFile(QString filePath);

    //使用Q_INVOKABLE来修饰成员函数，目的在于被修饰的成员函数能够被元对象系统所唤起。
    Q_INVOKABLE void openImage(QImage image);

    Q_INVOKABLE void openImageAndName(QImage image, QString imageName, QPoint point);

signals:

public slots:

private:
    int m_loadingCount;//启动次数
};

#endif // CUTOUTSCREENSHOTS_H
