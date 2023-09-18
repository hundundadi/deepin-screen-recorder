#include "leftwidget.h"
#include <QDebug>
#include <QPainter>
LeftWidget::LeftWidget(QWidget *parent)
{
    qInfo() << "正在初始化左侧界面...";
    initLeftUI();
    qInfo() << "左侧界面已初始化";
}

void LeftWidget::setImage(QImage image)
{
    m_image = image;
}

void LeftWidget::onShowImage(QImage image)
{
    m_image = image;
    update();
}

void LeftWidget::initLeftUI()
{

}


void LeftWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    if (!m_image.isNull()) {
        QPainter pp(this);
        QRect Temp(0, 0, this->width(), this->height());
        // 用rect获取到的图片不容易失帧
        //QImage tempImage = m_image.scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        pp.drawImage(Temp, m_image);
    }else{
        qInfo() << "当前图片为空！";
    }
}

LeftWidget::~LeftWidget()
{

}
