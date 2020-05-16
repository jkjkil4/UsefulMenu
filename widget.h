#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Ball;
class BtnList;

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void showNarrow();
    void showExpand();

    Ball *ball = nullptr;
    BtnList *btnList = nullptr;
};

#endif // WIDGET_H
