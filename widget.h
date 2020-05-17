#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

class Ball;
class BtnList;

//#define WIDGET_DEBUG

class Widget : public QWidget
{
    Q_OBJECT
protected:
    void mouseMoveEvent(QMouseEvent *) override;
#ifdef WIDGET_DEBUG
    void paintEvent(QPaintEvent *) override;
#endif

public:
    Widget(QWidget *parent = nullptr);
    ~Widget() override = default;

    void showNarrow();
    void showExpand();

    Ball *ball = nullptr;
    BtnList *btnList = nullptr;

public slots:
    void onCheckMouse();

    void onGetScreen();
    void onShowShortcut();

private:
    QTimer *checkMouse = new QTimer(this);

    bool isMoving = false;

    int maxHeight = 32;
};

#endif // WIDGET_H
