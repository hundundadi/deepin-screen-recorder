#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include <QWidget>

class LeftWidget :public QWidget
{
    Q_OBJECT
public:
     LeftWidget(QWidget *parent = nullptr);
    ~LeftWidget() override;
    void setImage(QImage image);

public slots:
    void onShowImage(QImage image);

protected:
    void initLeftUI();
    void paintEvent(QPaintEvent *e) override;

private:
    QImage m_image; //图片

};

#endif // LEFTWIDGET_H
