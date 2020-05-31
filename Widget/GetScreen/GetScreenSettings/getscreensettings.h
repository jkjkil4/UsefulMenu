#ifndef GETSCREENSETTINGS_H
#define GETSCREENSETTINGS_H

#include <QWidget>

#include <QPainter>
#include <QDebug>

class GetScreenSettings : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *) override;

public:
    explicit GetScreenSettings(QWidget *parent = nullptr);
    ~GetScreenSettings() override;

private:
    enum SaveScreenshotMode { G, D };
};

#endif // GETSCREENSETTINGS_H
