#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "Widget/ButtonTable/buttontable.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

class Widget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent*) override;

public:
    explicit Widget(QWidget *parent = nullptr);

private:
    ButtonTable* btnTable = new ButtonTable(this);
};

#endif // WIDGET_H
