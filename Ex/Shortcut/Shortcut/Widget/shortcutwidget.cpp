#include "shortcutwidget.h"

QAction ShortcutWidget::actOpenDir("打开所在文件夹");
QAction ShortcutWidget::actDelete("删除");

ShortcutWidget::ShortcutWidget(QWidget *parent)
    : QWidget(parent)
{
    //创建控件
    btnTable = new ButtonTable;
    connect(btnTable, SIGNAL(clicked(ButtonTableItem*)), this, SLOT(onBtnTableClicked(ButtonTableItem*)));
    connect(btnTable, SIGNAL(appendAction(QMenu*, ButtonTableItem*)), this, SLOT(onAppendAction(QMenu*, ButtonTableItem*)));
    connect(btnTable, SIGNAL(checkAction(QAction*, ButtonTableItem*)), this, SLOT(onCheckAction(QAction*, ButtonTableItem*)));


    MenuBar *menuBar = new MenuBar;
    menuBar->setMaximumHeight(26);
    menuBar->setMinimumHeight(26);
    connect(menuBar, &MenuBar::wndMoveOffset, [=](int xOffset, int yOffset){
        int toX = x() + xOffset, toY = y() + yOffset;
        QRect screenRect =  QGuiApplication::primaryScreen()->availableVirtualGeometry();
        toX = qBound(0, toX, screenRect.width() - width());
        toY = qBound(0, toY, screenRect.height() - height());
        move(toX, toY);
    });
    connect(menuBar, &MenuBar::wndClose, [=]{
        curShortcutWidget = nullptr;
        close();
    });
    connect(menuBar, &MenuBar::wndBack, [=]{
        (funcWidget->*func)();
        curShortcutWidget = nullptr;
        close();
    });
    connect(menuBar, &MenuBar::newItem, [=]{
        QAction actAddFile("添加文件");
        QAction actAddDir("添加文件夹");
        QAction actAddPath("添加路径");

        QMenu menu;
        menu.addActions(QList<QAction*>() << &actAddFile << &actAddDir << &actAddPath);
        menu.move(cursor().pos());
        QAction* res = menu.exec();

        if(res == &actAddFile || res == &actAddDir) {
            QSettings config("Config/Shortcut.ini", QSettings::IniFormat);
            QString path = config.value("config/dialogPath", "").toString();

            QString filePath = res == &actAddFile
                    ? QFileDialog::getOpenFileName(this, QString(), path)
                    : QFileDialog::getExistingDirectory(this, QString(), path);

            if(filePath != "") {
                config.setValue("config/dialogPath", filePath);
                btnTable->addItem(new ShortcutItem(filePath));
            }
        } else if(res == &actAddPath) {
            PathDialog dialog;
            dialog.exec();
            QString &path = dialog.path;
            if(path != "") {
                btnTable->addItem(new ShortcutItem(path));
            }
        }
    });


    //读取路径
    QFile pathsFile("Config/ShortcutPaths");
    if(pathsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&pathsFile);
        while(!in.atEnd()) {
            btnTable->addItem(new ShortcutItem(in.readLine()));
        }
        pathsFile.close();
    }


    //创建布局
    QVBoxLayout *layMain = new QVBoxLayout;
    layMain->setMargin(2);
    layMain->setSpacing(0);
    layMain->addWidget(menuBar);
    layMain->addWidget(btnTable);

    setLayout(layMain);


    //设置窗口属性
    setWindowFlags(Qt::SubWindow | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Window);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_DeleteOnClose, true);
    adjustSize();
    resize(width(), 360);
}

ShortcutWidget::~ShortcutWidget() {
    QFile pathsFile("Config/ShortcutPaths");
    if(pathsFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&pathsFile);
        bool hasPrev = false;
        for(ButtonTableItem* item : btnTable->vItems) {
            if(hasPrev) {
                out << '\n';
            } else hasPrev = true;
            ShortcutItem* sItem = (ShortcutItem*)item;
            out << sItem->filePath;
        }
        pathsFile.close();
    }
}


void ShortcutWidget::onBtnTableClicked(ButtonTableItem *item) {
    ShortcutItem *sItem = (ShortcutItem*)item;
    QString &path = sItem->filePath;
    path.replace('/', '\\');
    QDir dir;
    if(!dir.exists(path)) {
        QMessageBox::information(this, "提示", "路径不存在");
    } else {
        QFileInfo info(path);
        if( info.isDir() ){
            QProcess::startDetached("cmd.exe", QStringList() << "/c" << "start" << "" << path);
        }else{
            QProcess::startDetached("cmd.exe",
                QStringList() << "/c" << "start" << "" << info.fileName(), info.path() );
        }
    }

    curShortcutWidget = nullptr;
    close();
}

void ShortcutWidget::onAppendAction(QMenu *menu, ButtonTableItem *) {
    menu->addSeparator();
    menu->addAction(&actOpenDir);
    menu->addSeparator();
    menu->addAction(&actDelete);
}

void ShortcutWidget::onCheckAction(QAction *resAction, ButtonTableItem *item) {
    if(resAction == &actOpenDir) {
        ShortcutItem *sItem = (ShortcutItem*)item;
        QProcess::startDetached("cmd.exe", QStringList() << "/c" << "start" << "" << QFileInfo(sItem->filePath).path());
    } else if(resAction == &actDelete) {
        btnTable->removeItem(item);
    }
}


void ShortcutWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    jDrawRecFrame(&p, 0, 0, width(), height(), 2, QColor(102, 204, 255));
}

