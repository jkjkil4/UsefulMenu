#ifndef STATEBALL_H
#define STATEBALL_H

#include "stateball_global.h"

#include <QWidget>

#include <QAction>
#include <QMenu>

#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <QGuiApplication>
#include <QScreen>

#include <JQCPUMonitor>
#include "rammonitor.h"


extern "C" {
    STATEBALLSHARED_EXPORT QString getLibName();
    STATEBALLSHARED_EXPORT QPixmap getLibPixmap();
    STATEBALLSHARED_EXPORT void Main(QWidget*);
}


class StateBall : public QWidget
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent* ev) override;
    void mouseMoveEvent(QMouseEvent* ev) override;
    void mouseReleaseEvent(QMouseEvent* ev) override;
    void paintEvent(QPaintEvent*) override;

public:
    explicit StateBall(QWidget *parent = nullptr);
    ~StateBall() override = default;

private slots:
    void onGetState();

private:
    QTimer* timerGetState = new QTimer(this);

    //CPU使用率
    double cpuUsage = 0;
    int cpuArc = 0;
    //内存使用率
    double ramUsage = 0;
    int ramArc = 0;

    QPoint mousePosStart;
};

#endif // STATEBALL_H
