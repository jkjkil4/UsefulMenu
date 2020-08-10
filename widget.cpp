#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    //读取库
    QDir dir("Extensions");
    QStringList extensions = dir.entryList(QDir::Files);
    for(QString& extension : extensions) {
        vLibs.append(new QLibrary("Extensions/" + extension));
    }


    //创建控件
    connect(btnTable, SIGNAL(clicked(void*)), this, SLOT(onBtnTableClicked(void*)));
    for(QLibrary* lib : vLibs) {
        auto item = new ExtensionItem(lib);
        btnTable->addItem(item);
    }

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(btnTable);
    setLayout(layout);


    //设置窗口属性
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);


    //调整大小
    adjustSize();
    resize(width(), 608);
}

void Widget::onBtnTableClicked(void *item) {
    QTime t;
    t.start();
    ExtensionItem* extension = (ExtensionItem*)item;
    extension->libManager.fNewHandle();
    qDebug() << t.elapsed();
}

void Widget::paintEvent(QPaintEvent *){
    QPainter p(this);
    jDrawRecFrame(p, 0, 0, width(), height(), layout()->margin(), QColor(102, 204, 255, 200));
}

