#ifndef RIGHTWIDGET_H
#define RIGHTWIDGET_H

#include <QWidget>

class RightWidget :public QWidget
{
    Q_OBJECT
public:
    RightWidget(QWidget *parent = nullptr);
    ~RightWidget() override;


protected:
    void initRightUI();
};

#endif // RIGHTWIDGET_H
