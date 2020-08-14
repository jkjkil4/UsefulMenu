#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDir>
#include <QProcess>

#include "namespace.h"
#include "Class/lib.h"
#include "Class/globalshortcut.h"
#include "Class/libmanager.h"

#include "shortcutedit.h"

class SettingsWidget : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsWidget(QVector<Lib>& vLibs, QWidget *parent = nullptr);
    ~SettingsWidget() override = default;

private slots:
    void onOpenExDir();
    void onClose();

private:
    QVector<Lib>& vLibs;

    QListWidget *listWidget;
};

#endif // SETTINGSWIDGET_H
