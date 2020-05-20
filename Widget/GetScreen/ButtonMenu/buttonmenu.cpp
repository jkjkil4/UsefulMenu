#include "buttonmenu.h"

#include "Class/iconbtn.h"
#include "Class/line.h"

ButtonMenu::ButtonMenu(QWidget *parent) : QWidget(parent)
{
    layout = new QHBoxLayout;
    setLayout(layout);
}


void ButtonMenu::addWidget(QWidget *btn) {
    layout->addWidget(btn);
}

void ButtonMenu::addLine() {
    layout->addWidget(new Line(Qt::Horizontal));
}
