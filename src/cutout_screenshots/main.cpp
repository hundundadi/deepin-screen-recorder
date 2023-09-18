#include "cutoutscreenshots.h"
#include "ui/mainwindow.h"
#include "dbusservice/cutoutscreenshotsinterface.h"
#include "dbusservice/dbuscutoutscreenshotsadaptor.h"

#include <DWidget>
#include <DLog>
#include <DWindowManagerHelper>
#include <DWidgetUtil>
#include <DGuiApplicationHelper>
#include <DApplication>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    if (argc < 2) {
        qDebug() << "Can't open a null file";
        return 0;
    }

    DGuiApplicationHelper::setUseInactiveColorGroup(false);
#if(DTK_VERSION < DTK_VERSION_CHECK(5,4,0,0))
    DApplication::loadDXcbPlugin();
    QScopedPointer<DApplication> app(new DApplication(argc, argv));
#else
    QScopedPointer<DApplication> app(DApplication::globalApplication(argc, argv));
#endif
    app->setOrganizationName("deepin");
    app->setApplicationName("deepin-cutout-recorder");
    app->setProductName(QObject::tr("Cutout Screenshots"));
    app->setApplicationVersion("1.0");

    Dtk::Core::DLogManager::registerConsoleAppender();
    Dtk::Core::DLogManager::registerFileAppender();

    QString logPath = Dtk::Core::DLogManager::getlogFilePath();
    logPath.replace("deepin-screen-recorder.log", "deepin-cutout-screen.log");
    Dtk::Core::DLogManager::setlogFilePath(logPath);
    qDebug() << "日志位置: " << Dtk::Core::DLogManager::getlogFilePath();
    QCommandLineOption dbusOption(QStringList() << "u" << "dbus", "Start  from dbus.");
    QCommandLineParser cmdParser;
    cmdParser.setApplicationDescription("deepin-cutout-screenshots");
    cmdParser.addHelpOption();
    cmdParser.addVersionOption();
    cmdParser.addOption(dbusOption);
    cmdParser.process(*app);

//    app->loadTranslator();


    CutoutScreenShots instance;
    QDBusConnection dbus = QDBusConnection::sessionBus();

    if (dbus.registerService("com.deepin.PinScreenShots")) {
        // 第一次启动
        // 注册Dbus服务和对象
        dbus.registerObject("/com/deepin/PinScreenShots", &instance);
        // 初始化适配器
        new DbusCutoutScreenShotsAdaptor(&instance);

        if (cmdParser.isSet(dbusOption)) {
            // 第一次调用以 --dbus参数启动
            qDebug() << "dbus register waiting!";
            return app->exec();
        }

        instance.openFile(QString(argv[1]));
        qDebug() << "抠图dbus服务已注册";

    } else {
        // 第二次运行此应用，
        // 调用DBus接口，处理交给第一次调用的进程
        // 本进程退退出
        CutoutScreenShotsInterface *cutoutS = new CutoutScreenShotsInterface("com.deepin.CutoutScreenShots", "/com/deepin/PinScreenShots", QDBusConnection::sessionBus(), &instance);
        qDebug() << __FUNCTION__ << __LINE__;
        cutoutS->openFile(QString(argv[1]));
        delete cutoutS;
        return 0;
    }
    return app->exec();
}
