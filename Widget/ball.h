#ifndef BALL_H
#define BALL_H

#include <QWidget>
#include <QMouseEvent>
#include <QTimer>

class Ball : public QWidget
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void paintEvent(QPaintEvent *);

public:
    explicit Ball(QWidget *parent = nullptr);

signals:
    void wndShowNarrow();
    void wndShowExpand();
    void wndMoveOffset(int xOffset, int yOffset);
    void closeWidget();

public slots:
    void onCheckUsage();

private:
    QTimer *checkUsage = new QTimer(this);

    //CPU使用率
    double cpuUsage = 0;
    int cpuArc = 0;
    //内存使用率
    double ramUsage = 0;
    int ramArc = 0;

    //鼠标之前的位置
    QPoint mousePosStart;
};

#endif // BALL_H
