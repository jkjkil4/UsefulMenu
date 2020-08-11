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
    MenuBar* menuBar = new MenuBar;
    menuBar->setObjectName("MenuBar");
    menuBar->setStyleSheet("#MenuBar{background-color:rgb();}");
    menuBar->setMaximumHeight(26);
    menuBar->setMinimumHeight(26);
    connect(menuBar, &MenuBar::wndClose, [=]{ verifyClose(); });
    connect(menuBar, &MenuBar::wndHide, [=]{ hide(); });
    connect(menuBar, &MenuBar::wndMoveOffset, [=](int xOffset, int yOffset){
        int toX = x() + xOffset, toY = y() + yOffset;

        QRect screenRect =  QGuiApplication::primaryScreen()->availableVirtualGeometry();
        toX = qBound(0, toX, screenRect.width() - width());
        toY = qBound(0, toY, screenRect.height() - height());
        move(toX, toY);
    });

    connect(btnTable, SIGNAL(clicked(void*)), this, SLOT(onBtnTableClicked(void*)));
    for(QLibrary* lib : vLibs) {
        auto item = new ExtensionItem(lib);
        btnTable->addItem(item);
    }

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(2);
    layout->setSpacing(0);
    layout->addWidget(menuBar);
    layout->addWidget(btnTable);
    setLayout(layout);


    //创建系统托盘图标
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {      //判断系统是否支持系统托盘图标
        QMessageBox::information(this, "提示", "系统不支持托盘图标");
    } else {
        QAction* actExit = new QAction("退出(&Q)");
        connect(actExit, &QAction::triggered, [=]{ verifyClose(); });

        QMenu* menu = new QMenu((QWidget*)QApplication::desktop());
        menu->addAction(actExit);

        trayIcon = new QSystemTrayIcon(this);
        trayIcon->setIcon(QIcon(":/MainWidget/A.ico"));
        trayIcon->setContextMenu(menu);     //设置托盘菜单
        trayIcon->show();
        connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    }


    //设置窗口属性
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_QuitOnClose, true);


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

void MainWidget::verifyClose() {
    setVisible(true);
    int res = QMessageBox::information(this, "提示", "确认要退出吗", QMessageBox::Yes, QMessageBox::No);
    if(res == QMessageBox::Yes)
        close();
}

void MainWidget::onBtnTableClicked(void *item) {
    //setVisible(false);
    ExtensionItem* extension = (ExtensionItem*)item;
    extension->libManager.fMain();
}

void MainWidget::iconActivated(QSystemTrayIcon::ActivationReason reason) {
    switch(reason) {
    case QSystemTrayIcon::DoubleClick:
        setVisible(true);
        moveToProperPos();
        break;
    default:

        break;
    }
}

void MainWidget::paintEvent(QPaintEvent *){
    QPainter p(this);
    jDrawRecFrame(p, 0, 0, width(), height(), layout()->margin(), QColor(102, 204, 255));
}

