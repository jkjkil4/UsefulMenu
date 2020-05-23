#include "autoclosewidget.h"


AutoCloseWidget::AutoCloseWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlag(Qt::Popup);
}

void AutoCloseWidget::mousePressEvent(QMouseEvent *ev) {
    setAttribute(Qt::WA_NoMouseReplay);
    QWidget::mousePressEvent(ev);
}
