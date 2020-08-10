#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    //读取库
    QDir dir("Extensions");
    QStringList extensions = dir.entryList(QDir::Files);
    for(QString& extension : extensions) {
        vLibs.append(new QLibrary("Extensions/" + extension, this));
    }


    //创建控件
    connect(btnTable, SIGNAL(clicked(void*)), this, SLOT(onBtnTableClicked(void*)));
    for(QLibrary* lib : vLibs) {
        auto item = new ExtensionItem(lib);
        btnTable->addItem(item);
    }

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(0);
    layout->addWidget(btnTable);
    setLayout(layout);


    //设置窗口属性
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_DeleteOnClose, true);


    //调整大小
    adjustSize();
    resize(width(), 400);

    moveToProperPos();
}

void MainWidget::moveToProperPos() {
    QPoint mouse = cursor().pos();
    int toX = mouse.x() - width() / 2;
    int toY = mouse.y() - height() / 2;

    QRect screenRect =  QGuiApplication::primaryScreen()->availableVirtualGeometry();
    toX = qBound(0, toX, screenRect.width() - width());
    toY = qBound(0, toY, screenRect.height() - height());

    move(toX, toY);
}

void MainWidget::onBtnTableClicked(void *item) {
    //setVisible(false);
    ExtensionItem* extension = (ExtensionItem*)item;
    extension->libManager.fMain();
}

//void MainWidget::paintEvent(QPaintEvent *){
//    QPainter p(this);
//    jDrawRecFrame(p, 0, 0, width(), height(), layout()->margin(), QColor(102, 204, 255));
//}

