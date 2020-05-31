#ifndef BALL_H
#define BALL_H

#include <QWidget>

#include <QHBoxLayout>
#include <QMessageBox>

#include <QDir>
#include <QProcess>
#include <QMouseEvent>
#include <QTimer>

class Ball : public QWidget
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void paintEvent(QPaintEvent *) override;

public:
    explicit Ball(QWidget *parent = nullptr);
    ~Ball() override = default;

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
