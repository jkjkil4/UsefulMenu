#ifndef BUTTONTABLE_H
#define BUTTONTABLE_H

#include <QWidget>

#include "buttontableitem.h"
#include "namespace.h"

#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>

#include <QDebug>

class ButtonTable : public QWidget
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent* ev) override;
    void mouseMoveEvent(QMouseEvent* ev) override;
    void mouseReleaseEvent(QMouseEvent* ev) override;
    void wheelEvent(QWheelEvent* ev) override;
    void paintEvent(QPaintEvent*) override;

public:
    explicit ButtonTable(QWidget *parent = nullptr);
    ~ButtonTable() override;

    //按钮的属性
    SC int btnWidth = 64;
    SC int btnHeight = 64;
    SC int btnXCount = 4;
    SC int btnSpacing = 2;
    SC int margin = 2;

    //根据按钮的属性调整宽度
    void adjustWidth();

    //添加item
    void addItem(ButtonTableItem* item);

    //得到鼠标坐标对应的index
    int getIndex(QPoint mouse);

signals:
    //当item被点击时发出的信号
    void clicked(ButtonTableItem*);

private slots:
    void onTimerUpdateOffset();

private:
    //存放item的指针的QVector
    QVector<ButtonTableItem*> vItems;

    //鼠标对应的index
    int mouseIndex = -1;
    //鼠标是否按下
    bool isHolding = false;

    //用来对yOffset进行计算的timer
    QTimer* timerUpdateOffset = new QTimer(this);
    //速度
    int spd = 0;
    //纵坐标的偏移
    int yOffset = 0;

    void startTimerUpdate();
    QTimer* timerUpdate = new QTimer(this);
    SC int timerDelayMs = 8;
};

#endif // BUTTONTABLE_H
