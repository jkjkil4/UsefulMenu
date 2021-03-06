#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    QSettings config(APP_DIR + "/Config/UsefulMenu.ini", QSettings::IniFormat);

    globalShortcut = new QxtGlobalShortcut(this);
    if(!globalShortcut->setShortcut(QKeySequence(config.value("config/GlobalShortcut", "Alt+Q").toString())))
        QMessageBox::warning(this, "警告", "快捷键被占用或无效");

    connect(globalShortcut, &QxtGlobalShortcut::activated, [=]{ myShow(); });

    //读取哪些库被禁用了
    QVector<QString> vDisabledLib;
    QFile fileDisabledLib(APP_DIR + "/Config/DisabledLib");
    if(fileDisabledLib.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fileDisabledLib);
        while(!in.atEnd()) {
            vDisabledLib.append(in.readLine());
        }
        fileDisabledLib.close();
    }

    //读取库
    QDir dir(APP_DIR + "/Extensions");
    QStringList extensions = dir.entryList(QDir::Files);
    for(QString& extension : extensions) {
        QLibrary* lib = new QLibrary("Extensions/" + extension, this);
        vLibs.append({lib, !vDisabledLib.contains(getLibFileName(lib))});
    }

    //读取库顺序
    QMap<QString, int> libOrderMap;
    QFile fileLibOrder(APP_DIR + "/Config/LibOrder");
    if(fileLibOrder.open(QIODevice::ReadOnly | QIODevice::Text)) {
        int order = 1;
        QTextStream in(&fileLibOrder);
        while(!in.atEnd()) {
            libOrderMap[in.readLine()] = order;
            order++;
        }
        fileLibOrder.close();
    }

    //对库进行排序
    std::sort(vLibs.begin(), vLibs.end(), [=](Lib& a, Lib& b) -> bool { return getLibOrder(libOrderMap, a.lib) > getLibOrder(libOrderMap, b.lib); });

    //创建控件
    MenuBar* menuBar = new MenuBar;
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
    connect(menuBar, &MenuBar::onSettingsClicked, [=]{
        SettingsWidget(vLibs).exec();
        addLibsToBtnTable();
    });
    connect(menuBar, &MenuBar::onAboutClicked, [=]{
        QAction actAbout("关于");
        QAction actAboutQt("关于Qt");

        QMenu menu;
        menu.addActions(QList<QAction*>() << &actAbout << &actAboutQt);
        menu.move(cursor().pos());
        QAction* res = menu.exec();

        if(res == &actAbout) {
            QMessageBox::about(this, "关于",
                               "作者: jkjkil4<br>"
                               "github: <a href = https://github.com/jkjkil4/UsefulMenu>https://github.com/jkjkil4/UsefulMenu</a><br>"
                               "反馈问题: jkjkil@qq.com");
        } else if(res == &actAboutQt) {
            QMessageBox::aboutQt(this);
        }
    });

    connect(btnTable, SIGNAL(clicked(ButtonTableItem*)), this, SLOT(onBtnTableClicked(ButtonTableItem*)));
    connect(btnTable, SIGNAL(itemMoved(ButtonTableItem*, ButtonTableItem*)), this, SLOT(onBtnTableItemMoved(ButtonTableItem*, ButtonTableItem*)));
    connect(btnTable, &ButtonTable::appendAction, [](QMenu *menu, ButtonTableItem *item){
        ((ExtensionItem*)item)->libManager.fAppendAction(menu);
    });
    connect(btnTable, &ButtonTable::checkAction, [](QAction *act, ButtonTableItem *item) {
        ((ExtensionItem*)item)->libManager.fCheckAction(act);
    });
    addLibsToBtnTable();

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(2);
    layout->setSpacing(0);
    layout->addWidget(menuBar);
    layout->addWidget(btnTable);
    setLayout(layout);


    //设置窗口属性
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_QuitOnClose, true);


    //调整大小
    adjustSize();
    resize(width(), 360);

    moveToProperPos();


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

        trayIcon->showMessage("提示", "UsefulMenu已经启动", QSystemTrayIcon::MessageIcon::NoIcon);
    }

    setFocusPolicy(Qt::ClickFocus);
    setFocus();
}

MainWidget::~MainWidget() {
    QSettings config(APP_DIR + "/Config/UsefulMenu.ini", QSettings::IniFormat);
    config.setValue("config/GlobalShortcut", globalShortcut->shortcut().toString());

    //记录被禁用的库
    QFile fileDisabledLib(APP_DIR + "/Config/DisabledLib");
    if(fileDisabledLib.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&fileDisabledLib);
        bool hasPrev = false;
        for(auto& lib : vLibs) {
            if(!lib.isEnabled) {
                if(hasPrev)
                    out << '\n';
                else hasPrev = true;
                out << getLibFileName(lib.lib);
            }
        }
        fileDisabledLib.close();
    }

    //记录库的顺序
    QFile fileLibOrder(APP_DIR + "/Config/LibOrder");
    if(fileLibOrder.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&fileLibOrder);
        bool hasPrev = false;
        for(auto iter = vLibs.rbegin(); iter < vLibs.rend(); iter++) {
            if(hasPrev)
                out << '\n';
            else hasPrev = true;
            out << getLibFileName((*iter).lib);
        }
        fileLibOrder.close();
    }
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

void MainWidget::myShow() {
    moveToProperPos();
    setVisible(true);
}

void MainWidget::verifyClose() {
    setVisible(true);
    int res = QMessageBox::information(this, "提示", "确认要退出吗", QMessageBox::Yes, QMessageBox::No);
    if(res == QMessageBox::Yes)
        close();
}

void MainWidget::addLibsToBtnTable() {
    btnTable->clearItem();
    for(auto& lib : vLibs) {
        if(lib.isEnabled) {
            auto item = new ExtensionItem(lib.lib);
            item->libManager.fSetShowFuncPtr(this, (ShowFunc)&MainWidget::show);
            btnTable->addItem(item);
        }
    }
}

void MainWidget::onBtnTableClicked(ButtonTableItem *item) {
    setVisible(false);
    ExtensionItem* extension = (ExtensionItem*)item;
    extension->libManager.fMain(this);
}

void MainWidget::onBtnTableItemMoved(ButtonTableItem *item1, ButtonTableItem *item2) {
    ExtensionItem *exItem1 = (ExtensionItem*)item1, *exItem2 = (ExtensionItem*)item2;
    auto iter1 = vLibs.end(), iter2 = vLibs.end();
    for(auto iter = vLibs.begin(); iter < vLibs.end(); iter++) {
        if((*iter).lib == exItem1->libManager.lib) {
            iter1 = iter;
            break;
        }
    }
    for(auto iter = vLibs.begin(); iter < vLibs.end(); iter++) {
        if((*iter).lib == exItem2->libManager.lib) {
            iter2 = iter;
            break;
        }
    }
    if(iter1 != vLibs.end() && iter2 != vLibs.end()) {
        Lib &lib1 = *iter1, &lib2 = *iter2;
        Lib tmpLib = lib1;
        lib1 = lib2;
        lib2 = tmpLib;
    }
}

void MainWidget::iconActivated(QSystemTrayIcon::ActivationReason reason) {
    switch(reason) {
    case QSystemTrayIcon::DoubleClick:
        myShow();
        break;
    default:

        break;
    }
}

void MainWidget::paintEvent(QPaintEvent *){
    QPainter p(this);
    jDrawRecFrame(p, 0, 0, width(), height(), layout()->margin(), QColor(102, 204, 255));
}

