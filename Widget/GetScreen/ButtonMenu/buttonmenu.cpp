#include "buttonmenu.h"


ButtonMenu::ButtonMenu(QWidget *parent) : QWidget(parent)
{
    layout = new QHBoxLayout;
    setLayout(layout);
}


void ButtonMenu::addWidget(QWidget *w) {
    layout->addWidget(w);
}

void ButtonMenu::setMargin(int margin) {
    layout->setMargin(margin);
}

void ButtonMenu::setSpcing(int spacing) {
    layout->setSpacing(spacing);
}

void ButtonMenu::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(1, 1, width(), height(), bgColor);
    jDrawRecFrame(&p, 0, 0, width(), height(), 1, bgColor.darker(140));
}
