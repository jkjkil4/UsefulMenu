#ifndef SHORTCUTWIDGET_H
#define SHORTCUTWIDGET_H

#include <QPushButton>
#include <QLabel>
#include <QListWidget>

#include <QCloseEvent>

#include "Class/autoclosewidget.h"

#include "Class/global.h"

#include "PathsView/pathbtn.h"

class PathDialog;

class ShortcutWidget : public AutoCloseWidget
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *ev) override;

public:
    explicit ShortcutWidget(QWidget *parent = nullptr);
    ~ShortcutWidget() override;

    inline void newItem(QString path);

    //和大小相关的一些东西
    SC int xNum = 6;
    SC int totalWidth = xNum * PathBtn::bWidth;
    SC int totalHeight = 240;

public slots:
    void onBtnAddFileClicked();
    void onBtnAddDirClicked();
    void onBtnAddPathClicked();

private:
    PathDialog *pathDialog = nullptr;
    QListWidget *listWidget = new QListWidget;

    bool hasChildWindow = false;
};

#endif // SHORTCUTWIDGET_H
