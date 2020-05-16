#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Ball;
class BtnList;

#define WIDGET_DEBUG

class Widget : public QWidget
{
    Q_OBJECT
protected:
#ifdef WIDGET_DEBUG
    void paintEvent(QPaintEvent *);
#endif

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void showNarrow();
    void showExpand();

    Ball *ball = nullptr;
    BtnList *btnList = nullptr;

private:
    int maxHeight = 32;
};

#endif // WIDGET_H
