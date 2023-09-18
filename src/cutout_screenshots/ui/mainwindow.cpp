#include "mainwindow.h"


#include <QDebug>
#include <QDBusInterface>
#include <QDesktopWidget>
#include <QScreen>
#include <QClipboard>
#include <QFileDialog>
#include <QDateTime>
#include <QHBoxLayout>
#include <QSplitter>
MainWindow::MainWindow(QWidget *parent)
    : DWidget(parent)
{
    initMainUI();
}

bool MainWindow::openFile(const QString &filePaths)
{
    qDebug() << "func: " << __func__ ;
    QImage image(filePaths);
    openImageAndName(image, "", QPoint(0, 0));
    return true;
}

bool MainWindow::openImage(const QImage &image)
{
    qDebug() << "func: " << __func__ ;
    openImageAndName(image, "", QPoint(0, 0));
    return true;
}

bool MainWindow::openImageAndName(const QImage &image, const QString &name, const QPoint &point)
{
    qDebug() << "func: " << __func__ << name;
    m_image = image;
    m_lastImagePath = name;
    m_imageName = QString(tr("Screenshot") + "_%1").arg(QDateTime::currentDateTime().
                                                        toString("yyyyMMddHHmmss"));
    int width = static_cast<int>(m_image.width() / m_pixelRatio);
    int height = static_cast<int>(m_image.height() / m_pixelRatio);
    //将窗口的大小重置为图片的大小
    resize(width, height);
    //将坐标点转换为m_pixelRatio屏幕缩放比下的点
    m_showPosition = QPoint(static_cast<int>(point.x() * m_pixelRatio), static_cast<int>(point.y() * m_pixelRatio));
    QRect currnetScreenRect;
    //查找当前截图贴图区域所在的屏幕(m_screenInfo中存储已缩放的数据）
    for (int i = 0; i < m_screenInfo.size(); ++i) {
        currnetScreenRect = {
            static_cast<int>(m_screenInfo[i].x),
            static_cast<int>(m_screenInfo[i].y),
            static_cast<int>(m_screenInfo[i].width *  m_pixelRatio),
            static_cast<int>(m_screenInfo[i].height * m_pixelRatio)
        };
        if (currnetScreenRect.contains(m_showPosition)) {
            int x = static_cast<int>((m_showPosition.x() - currnetScreenRect.x()) / m_pixelRatio + currnetScreenRect.x());
            m_showPosition.setX(x);
            int y = static_cast<int>((m_showPosition.y() - currnetScreenRect.y()) / m_pixelRatio + currnetScreenRect.y());
            m_showPosition.setY(y);
            break;
        }
    }
    //移动到指定位置
    move(m_showPosition);
    emit updateShowImage(m_image);
    m_proportion = static_cast<double>(this->width())  / this->height();
    m_isfirstTime = true; //解决119157Bug采用的标识
    return true;
}

// 获取贴图窗口的显示位置
QPoint MainWindow::getShowPosition()
{
    return m_showPosition;
}

void MainWindow::initMainUI()
{
    setFixedHeight(800);
    QHBoxLayout *hboxL = new QHBoxLayout(this);
    m_leftWidget = new LeftWidget();
    hboxL->addWidget(m_leftWidget);
    connect(this,&MainWindow::updateShowImage,m_leftWidget,&LeftWidget::onShowImage);
    m_rightWidget = new RightWidget();
    hboxL->addWidget(m_rightWidget);
    QSplitter *mainSplitter = new QSplitter(Qt::Horizontal); //新建水平分割器
    mainSplitter->setHandleWidth(5);//分割线的宽度
    mainSplitter->setLineWidth(5);
    mainSplitter->setChildrenCollapsible(false);//不允许把分割出的子窗口拖小到0，最小值被限定为sizeHint或maxSize/minSize
    mainSplitter->addWidget(m_leftWidget);//把ui中拖出的各个控件拿走，放到分割器里面
    mainSplitter->addWidget(m_rightWidget);
    QList<int> list;
    //默认右侧识栏目是220的宽度
    list << 600 << 200;
    mainSplitter->setSizes(list);
    hboxL->addWidget(mainSplitter);

    this->setLayout(hboxL);
}

MainWindow::~MainWindow()
{

}
