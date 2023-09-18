// Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "leftwidget.h"
#include "rightwidget.h"

#include <DWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QDebug>
#include <QApplication>
#include <QShortcut>

DWIDGET_USE_NAMESPACE

#define PADDING 10
/**
 * @brief 贴图的主界面
 */
class MainWindow : public DWidget
{
    Q_OBJECT
    enum Direction { UP = 0, DOWN = 1, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };
    struct ScreenInfo {
        int x;
        int y;
        int width;
        int height;
        QString name;
        ~ScreenInfo() {}
    };

//public:
//    static bool isWaylandProtocol();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief 打开图片
     * @param 图片的路径
     * @return 打开是否成功
     */
    bool openFile(const QString &filePaths);

    /**
     * @brief 打开图片
     * @param 图片对象
     * @return
     */
    bool openImage(const QImage &image);

    /**
     * @brief 打开图片
     * @param 图片对象
     * @param 图片名称
     * @return
     */
    bool openImageAndName(const QImage &image, const QString &name = "", const QPoint &point = QPoint(0, 0));

    /**
     * @brief 获取贴图窗口的显示位置
     */
    QPoint getShowPosition();
protected:
    void initMainUI();

signals:
    void updateShowImage(QImage);
private:
    /**
     * @brief 保存贴图窗口的显示位置
     */
    QPoint m_showPosition;
    QImage m_image; //图片
    QString m_imageName; //图片名称
    QString m_lastImagePath; // 上一次图片的保存路径

    /**
     * @brief 屏幕的缩放比例
     * 当屏幕缩放比例为1.25时，此时的屏幕实际大小为1536*864
     *   1.1.如果需将当前屏幕的点换算到1920*1080上需乘上m_pixelRatio
     *   1.2.如果需将1920*1080上的点换算到此屏幕应该除以m_pixelRatio
     */
    qreal m_pixelRatio = 1.0;
    QList<ScreenInfo> m_screenInfo; //所有屏幕信息

    double m_proportion = 0.0; //宽高比
    bool m_isfirstTime = false;

    LeftWidget* m_leftWidget;
    RightWidget* m_rightWidget;


};

#endif // MAINWINDOW_H
