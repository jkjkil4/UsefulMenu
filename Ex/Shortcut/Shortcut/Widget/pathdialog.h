#ifndef PATHDIALOG_H
#define PATHDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDir>
#include <QTimer>

class PathDialog : public QDialog
{
public:
    PathDialog();

    QString path;

private:
    QTimer *delayTimer = new QTimer(this);

    QPushButton *btnAccept, *btnCancel;
};

#endif // PATHDIALOG_H
