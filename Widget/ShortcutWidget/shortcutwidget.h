#ifndef SHORTCUTWIDGET_H
#define SHORTCUTWIDGET_H

#include <QPushButton>
#include <QLabel>

#include <QCloseEvent>

#include "Class/autoclosewidget.h"

#include "PathsView/pathsview.h"

class PathDialog;

class ShortcutWidget : public AutoCloseWidget
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *ev) override;

public:
    explicit ShortcutWidget(QWidget *parent = nullptr);
    ~ShortcutWidget() override = default;

public slots:
    void onBtnAddFileClicked();
    void onBtnAddDirClicked();
    void onBtnAddPathClicked();

private:
    QList<PathBtn*> paths;

    PathDialog *pathDialog = nullptr;
    PathsView *pathsView = nullptr;


    bool hasChildWindow = false;
};

#endif // SHORTCUTWIDGET_H
