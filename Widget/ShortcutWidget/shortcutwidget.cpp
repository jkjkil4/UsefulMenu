#include "shortcutwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>
#include <QFileInfo>
#include <QTextStream>

#include <QDebug>
#include <QScrollBar>

#include "PathDialog/pathdialog.h"


#define PATH_DIALOG(pathFunc)\
    QSettings config("settings.ini", QSettings::IniFormat);\
    QString pathBefore = config.value("path/addFileOrDirPath", "").toString();\
    hasChildWindow = true;\
    QString path = QFileDialog::pathFunc(this, QString(), pathBefore);\
    hasChildWindow = false;\
    if(path != "") {\
        config.setValue("path/addFileOrDirPath", QFileInfo(path).path());\
        newItem(path);\
    }\



ShortcutWidget::ShortcutWidget(QWidget *parent)
    : AutoCloseWidget(parent)
{
    QHBoxLayout *layTop = new QHBoxLayout;
    layTop->setMargin(2);
    layTop->setSpacing(2);
    layTop->addStretch();

    QPushButton *btnAddFile = new QPushButton("添加文件");
    QPushButton *btnAddDir = new QPushButton("添加文件夹");
    QPushButton *btnAddPath = new QPushButton("添加路径");

    QLabel *titleLabel = new QLabel("快捷方式");
    QFont font = titleLabel->font();
    font.setPointSize(12);
    titleLabel->setFont(font);

    layTop->addWidget(titleLabel);
    layTop->addStretch(2);
    layTop->addWidget(btnAddFile);
    layTop->addWidget(btnAddDir);
    layTop->addWidget(btnAddPath);
    connect(btnAddFile, SIGNAL(clicked()), this, SLOT(onBtnAddFileClicked()));
    connect(btnAddDir, SIGNAL(clicked()), this, SLOT(onBtnAddDirClicked()));
    connect(btnAddPath, SIGNAL(clicked()), this, SLOT(onBtnAddPathClicked()));


    pathDialog = new PathDialog;
    pathDialog->setVisible(false);
    connect(pathDialog, &PathDialog::accepted, [=]{
        newItem(pathDialog->text());
    });
    connect(pathDialog, &PathDialog::hided, [=]{
        listWidget->setVisible(true);
        adjustSize();
    });


    listWidget->setViewMode(QListView::IconMode);
    listWidget->setMovement(QListView::Static);
    listWidget->setSpacing(0);
    listWidget->setFrameStyle(QFrame::NoFrame);
    listWidget->setObjectName("PathListWidget");
    listWidget->setStyleSheet("#PathListWidget{background-color: rgb(200, 200, 200);}");
    listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->verticalScrollBar()->adjustSize();
    limitSize(listWidget, totalWidth + 2 + listWidget->verticalScrollBar()->width(), totalHeight);


    QVBoxLayout *layMain = new QVBoxLayout;
    layMain->setMargin(2);
    layMain->setSpacing(0);
    layMain->addLayout(layTop);
    layMain->addWidget(pathDialog);
    layMain->addWidget(listWidget);
    setLayout(layMain);

    //设置属性
    setObjectName("ShortcutWidget");
    setStyleSheet("#ShortcutWidget{background-color: rgb(220, 220, 220);}");
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_DeleteOnClose);
    adjustSize();
    limitWidth(this, width());

    //读取路径
    QDir dir;
    if(dir.exists("paths.txt")) {
        QFile file("paths.txt");
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            hasChildWindow = true;
            QMessageBox::warning(this, "错误", "读取路径失败");
            hasChildWindow = false;
        } else {
            QTextStream in(&file);
            while(!in.atEnd()) {
                QString path = in.readLine().simplified().trimmed();
                if(path != "")
                    newItem(path);
            }
            file.close();
        }
    }
}

ShortcutWidget::~ShortcutWidget() {
    //关闭时保存路径
    QFile file("paths.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "保存路径失败");
    } else {
        QTextStream out(&file);
        for(int i = 0; i < listWidget->count(); i++) {
            QListWidgetItem *item = listWidget->item(i);
            PathBtn *btn = (PathBtn*)listWidget->itemWidget(item);
            out << btn->getPath() << "\n";
        }
        file.close();
    }
}


inline void ShortcutWidget::newItem(QString path) {
    QListWidgetItem *item = new QListWidgetItem(listWidget);
    item->setSizeHint(QSize(PathBtn::bWidth, PathBtn::bHeight));
    listWidget->setItemWidget(item, new PathBtn(path));
}


void ShortcutWidget::onBtnAddFileClicked() {
    PATH_DIALOG(getOpenFileName);
}

void ShortcutWidget::onBtnAddDirClicked() {
    PATH_DIALOG(getExistingDirectory);
}

void ShortcutWidget::onBtnAddPathClicked() {
    listWidget->setVisible(false);
    pathDialog->setVisible(true);
    pathDialog->setFocusToLineEdit();
    adjustSize();
}


void ShortcutWidget::closeEvent(QCloseEvent *ev) {
    if(hasChildWindow) {    //如果有关联的窗口，则不关闭
        ev->ignore();
    }
}


