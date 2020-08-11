#include "menubar.h"

MenuBar::MenuBar(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(1);
    layout->addWidget(btnExit);
    layout->addStretch();
    layout->addWidget(btnAbout);
    layout->addWidget(btnSettings);
    layout->addWidget(btnHide);

    setLayout(layout);

    btnExit->setToolTip("退出");
    connect(btnExit, &IconBtn::clicked, [=]{ emit wndClose(); });

    btnAbout->setToolTip("帮助/关于");

    btnSettings->setToolTip("设置");

    btnHide->setToolTip("隐藏");
    connect(btnHide, &IconBtn::clicked, [=]{ emit wndHide(); });
}

void MenuBar::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        mousePosStart = ev->pos();
    }
}

void MenuBar::mouseMoveEvent(QMouseEvent *ev) {
    if(ev->buttons() & Qt::LeftButton) {
        QPoint mousePos = ev->pos();
        int xOffset = mousePos.x() - mousePosStart.x();
        int yOffset = mousePos.y() - mousePosStart.y();
        emit wndMoveOffset(xOffset, yOffset);
    }
}

void MenuBar::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), QColor(102, 204, 255));
}
