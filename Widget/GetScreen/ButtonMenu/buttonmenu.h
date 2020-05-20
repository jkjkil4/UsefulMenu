#ifndef BUTTONMENU_H
#define BUTTONMENU_H

#include <QWidget>
#include <QHBoxLayout>


class ButtonMenu : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonMenu(QWidget *parent = nullptr);

    void addWidget(QWidget *btn);
    void addLine();

private:
    QHBoxLayout *layout = nullptr;
};

#endif // BUTTONMENU_H
