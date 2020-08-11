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
    void keyPressEvent(QKeyEvent* ev) override {
        qDebug() << ev->text();
    }
    void paintEvent(QPaintEvent*) override;

public:
    struct Lib {
        QLibrary* lib;
        bool isEnabled;
    };

    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget() override;

    void moveToProperPos();

    void verifyClose();

    void addLibsToBtnTable();

private slots:
    void onBtnTableClicked(void* item);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    ButtonTable* btnTable = new ButtonTable;

    QSystemTrayIcon* trayIcon;

    QVector<Lib> vLibs;
};

inline QString getLibFileName(QLibrary* lib) {
    QString libName = QFileInfo(lib->fileName()).fileName();
    return libName.left(libName.lastIndexOf('.'));
}

inline int getLibOrder(const QMap<QString, int> &map, QLibrary *lib) {
    auto iter = map.find(getLibFileName(lib));
    if(iter == map.end())
        return 0;

    return *iter;
}

#endif // WIDGET_H
