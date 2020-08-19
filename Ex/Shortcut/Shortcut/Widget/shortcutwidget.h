#ifndef SHORTCUTWIDGET_H
#define SHORTCUTWIDGET_H

#include <QWidget>

#include <QVBoxLayout>
#include <QGuiApplication>
#include <QScreen>
#include <QFileDialog>
#include <QSettings>
#include <QFileInfo>
#include <QMessageBox>
#include <QProcess>
#include <QTextStream>

#include "buttontable.h"
#include "menubar.h"
#include "pathdialog.h"
#include "Class/shortcutitem.h"
#include "Class/global.h"
#include "header.h"

#include <QDebug>


class ShortcutWidget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent*) override;

public:
    explicit ShortcutWidget(QWidget *parent = nullptr);
    ~ShortcutWidget() override;

private slots:
    void onBtnTableClicked(ButtonTableItem *item);
    void onAppendAction(QMenu *menu, ButtonTableItem *);
    void onCheckAction(QAction *resAction, ButtonTableItem *item);

private:
    ButtonTable *btnTable;

    //QAction *actOpenDir = new QAction("打开所在文件夹");
    //QAction *actDelete = new QAction("删除");
    static QAction actOpenDir;
    static QAction actDelete;
};

#endif // SHORTCUTWIDGET_H
