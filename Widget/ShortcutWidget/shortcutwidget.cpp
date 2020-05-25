#include "shortcutwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>
#include <QFileInfo>
#include <QTextStream>

#include <QDebug>

#include "PathDialog/pathdialog.h"

#define PATH_DIALOG(pathFunc)\
    QSettings config("settings.ini", QSettings::IniFormat);\
    QString pathBefore = config.value("path/addFileOrDirPath", "").toString();\
    hasChildWindow = true;\
    QString path = QFileDialog::pathFunc(this, QString(), pathBefore);\
    hasChildWindow = false;\
    if(path != "") {\
        config.setValue("path/addFileOrDirPath", QFileInfo(path).path());\
        paths.push_back(new PathBtn(path, pathsView));\
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
        paths.push_back(new PathBtn(pathDialog->text(), pathsView));

    });
    connect(pathDialog, &PathDialog::hided, [=]{
        pathsView->setVisible(true);
        adjustSize();
    });


    pathsView = new PathsView(&paths);


    QVBoxLayout *layMain = new QVBoxLayout;
    layMain->setMargin(2);
    layMain->setSpacing(0);
    layMain->addLayout(layTop);
    layMain->addWidget(pathDialog);
    layMain->addWidget(pathsView);
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
                    paths.push_back(new PathBtn(path, pathsView));
            }
            file.close();
        }
    }
    pathsView->updateChildPos();
}


void ShortcutWidget::onBtnAddFileClicked() {
    PATH_DIALOG(getOpenFileName);
    pathsView->updateChildPos();
}

void ShortcutWidget::onBtnAddDirClicked() {
    PATH_DIALOG(getExistingDirectory);
    pathsView->updateChildPos();
}

void ShortcutWidget::onBtnAddPathClicked() {
    pathsView->setVisible(false);
    pathDialog->setVisible(true);
    adjustSize();
    pathsView->updateChildPos();
}


void ShortcutWidget::closeEvent(QCloseEvent *ev) {
    if(hasChildWindow) {    //如果有关联的窗口，则不关闭
        ev->ignore();
    } else {
        //关闭时保存路径
        QFile file("paths.txt");
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "错误", "保存路径失败");
        } else {
            QTextStream out(&file);
            for(auto pathBtn : paths)
                out << pathBtn->getPath() << "\n";
            file.close();
        }
    }
}
