#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "namespace.h"
#include "Class/extensionitem.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QDir>
#include <QTime>

class Widget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent*) override;

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override = default;

private slots:
    void onBtnTableClicked(void* item);

private:
    ButtonTable* btnTable = new ButtonTable;

    QVector<QLibrary*> vLibs;
};

#endif // WIDGET_H
