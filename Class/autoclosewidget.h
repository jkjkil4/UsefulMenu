#ifndef AUTOCLOSEWIDGET_H
#define AUTOCLOSEWIDGET_H

#include <QWidget>

#include <QMouseEvent>

class AutoCloseWidget : public QWidget
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *ev) override;

public:
    explicit AutoCloseWidget(QWidget *parent = nullptr);
    ~AutoCloseWidget() override = default;
};

#endif // AUTOCLOSEWIDGET_H
