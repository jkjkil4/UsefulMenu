#include "menubar.h"

MenuBar::MenuBar(QWidget *parent) : QWidget(parent)
{
    //创建控件
    IconBtn *btnBack = new IconBtn(QIcon(":/ShortcutBtn/Resource/Back.png"));
    btnBack->setToolTip("返回");
    connect(btnBack, &IconBtn::clicked, [=]{ emit wndBack(); });

    IconBtn *btnAdd = new IconBtn(QIcon(":/ShortcutBtn/Resource/Add.png"));
    btnAdd->setToolTip("添加");
    connect(btnAdd, &IconBtn::clicked, [=]{ emit newItem(); });

    IconBtn *btnClose = new IconBtn(QIcon(":/ShortcutBtn/Resource/Close.png"));
    btnClose->setToolTip("关闭");
    connect(btnClose, &IconBtn::clicked, [=]{ emit wndClose(); });


    //创建布局
    QHBoxLayout *layMain = new QHBoxLayout;
    layMain->setMargin(1);
    layMain->setSpacing(1);
    layMain->addWidget(btnBack);
    layMain->addStretch();
    layMain->addWidget(btnAdd);
    layMain->addWidget(btnClose);

    setLayout(layMain);
}


void MenuBar::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        mousePosStart = ev->pos();
    }
}

void MenuBar::mouseMoveEvent(QMouseEvent *ev) {
    if(ev->buttons() & Qt::LeftButton) {
        QPoint mouse = ev->pos();
        int xOffset = mouse.x() - mousePosStart.x();
        int yOffset = mouse.y() - mousePosStart.y();
        emit wndMoveOffset(xOffset, yOffset);
    }
}


void MenuBar::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), QColor(102, 204, 255));
}
