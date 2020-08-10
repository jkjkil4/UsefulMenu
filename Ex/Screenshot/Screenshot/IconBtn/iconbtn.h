#ifndef ICONBTN_H
#define ICONBTN_H

#include <QAbstractButton>

#include "header.h"

class IconBtn : public QAbstractButton
{
protected:
    void keyPressEvent(QKeyEvent *) override {}
    void keyReleaseEvent(QKeyEvent *) override {}
    void paintEvent(QPaintEvent *) override;

public:
    explicit IconBtn(QWidget *parent = nullptr);
    explicit IconBtn(QIcon icon, QWidget *parent = nullptr);
    ~IconBtn() override = default;

    bool checkMouseAt();

    VARIBLE_FUNC(ColorNormal, colorNormal, QColor)
    VARIBLE_FUNC(ColorMouseAt, colorMouseAt, QColor)
    VARIBLE_FUNC(ColorHolding, colorHolding, QColor)

private:
    QColor colorNormal = QColor(200,200,200);
    QColor colorMouseAt = QColor(220,220,220);
    QColor colorHolding = QColor(180,180,180);
};

#endif // ICONBTN_H
