#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QAction>
#include <QMenu>

#include <QMessageBox>

#include "namespace.h"
#include "Class/extensionitem.h"
#include "Widget/menubar.h"

#include <QVBoxLayout>

#include <QDir>
#include <QApplication>
#include <QGuiApplication>
#include <QSystemTrayIcon>
#include <QScreen>

class MainWidget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent*) override;

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget() override = default;

    void moveToProperPos();

    void verifyClose();

private slots:
    void onBtnTableClicked(void* item);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    ButtonTable* btnTable = new ButtonTable;

    QSystemTrayIcon* trayIcon;

    QVector<QLibrary*> vLibs;
};

#endif // WIDGET_H
