#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QAction>
#include <QMenu>

#include <QMessageBox>

#include "namespace.h"
#include "Class/extensionitem.h"
#include "Widget/menubar.h"
#include "Class/globalshortcut.h"

#include <QVBoxLayout>

#include <QDir>
#include <QApplication>
#include <QGuiApplication>
#include <QSystemTrayIcon>
#include <QScreen>

#include <QSettings>

class MainWidget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent*) override;

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget() override;

    void moveToProperPos();

    void myShow();
    void verifyClose();

    void addLibsToBtnTable();

private slots:
    void onBtnTableClicked(ButtonTableItem* item);
    void onBtnTableItemMoved(ButtonTableItem* item1, ButtonTableItem* item2);

    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    ButtonTable* btnTable = new ButtonTable;

    QSystemTrayIcon* trayIcon;

    QVector<Lib> vLibs;
};

#endif // WIDGET_H
