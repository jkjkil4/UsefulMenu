#include "settingswidget.h"

SettingsWidget::SettingsWidget(QVector<Lib> &vLibs, QWidget *parent)
    : QDialog(parent), vLibs(vLibs)
{
    //创建控件
    ShortcutEdit* shortcutEdit = new ShortcutEdit(globalShortcut, this);
    shortcutEdit->font.setPointSize(12);
    limitSize(shortcutEdit, 200, 28);

    QPushButton* btnOpenExDir = new QPushButton("打开功能文件所在文件夹");
    connect(btnOpenExDir, SIGNAL(clicked()), this, SLOT(onOpenExDir()));
    QPushButton* btnClose = new QPushButton("确定");
    connect(btnClose, SIGNAL(clicked()), this, SLOT(onClose()));

    listWidget = new QListWidget;
    limitHeight(listWidget, 200);
    for(Lib& lib : vLibs) {
        QString text = getLibFileName(lib.lib);
        LibManager::FuncLibName fLibName = (LibManager::FuncLibName)lib.lib->resolve("getLibName");
        if(fLibName)
            text += " (" + (*fLibName)() + ')';
        QListWidgetItem *item = new QListWidgetItem(text);
        item->setCheckState(lib.isEnabled ? Qt::Checked : Qt::Unchecked);
        listWidget->addItem(item);
    }

    //创建布局
    QHBoxLayout *layShortcutEdit = new QHBoxLayout;
    layShortcutEdit->setMargin(1);
    layShortcutEdit->setSpacing(3);
    layShortcutEdit->addWidget(new QLabel("设置快捷键"));
    layShortcutEdit->addWidget(shortcutEdit);

    QHBoxLayout *layListWidgetLabel = new QHBoxLayout;
    layListWidgetLabel->addWidget(new QLabel("设置功能是否可见"));
    layListWidgetLabel->addStretch();
    QVBoxLayout *layListWidget = new QVBoxLayout;
    layListWidget->setMargin(0);
    layListWidget->setSpacing(2);
    layListWidget->addLayout(layListWidgetLabel);
    layListWidget->addWidget(listWidget);

    QHBoxLayout *layBottom = new QHBoxLayout;
    layBottom->addWidget(btnOpenExDir);
    layBottom->addStretch();
    layBottom->addWidget(btnClose);

    QVBoxLayout *layMain = new QVBoxLayout;
    layMain->setSpacing(6);
    layMain->addLayout(layShortcutEdit);
    layMain->addLayout(layListWidget);
    layMain->addLayout(layBottom);
    layMain->setSizeConstraint(QVBoxLayout::SizeConstraint::SetFixedSize);

    setLayout(layMain);


    //设置窗口属性
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::SubWindow);
    setFocusPolicy(Qt::ClickFocus);
    adjustSize();
    setMaximumHeight(16777215);

}


void SettingsWidget::onOpenExDir() {
    QDir dir(APP_DIR);
    if(dir.cd("Extensions")) {
        QProcess::startDetached("explorer.exe Extensions");
    }
}

void SettingsWidget::onClose() {
    int count = listWidget->count();
    repeat(i, count) {
        vLibs[i].isEnabled = listWidget->item(i)->checkState() == Qt::Checked;
    }

    close();
}
