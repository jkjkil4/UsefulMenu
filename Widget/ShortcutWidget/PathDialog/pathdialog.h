#ifndef TEXTDIALOG_H
#define TEXTDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QDir>

/*
    pathdialog.h和pathdialog.cpp
    是我从personalProject里复制来的 (textdialog)
    有一些的修改
    懒得重新写了
*/

class PathDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PathDialog(QWidget *parent = nullptr);
    ~PathDialog() override = default;

    QString text();

    void onHide();

    void setFocusToLineEdit();

signals:
    void accpeted();
    void hided();

private:
    QLineEdit *lineEdit = new QLineEdit;
    QPushButton *btnAccept = new QPushButton("确定");
    QPushButton *btnCancel = new QPushButton("取消");
    QTimer *delayTimer = new QTimer(this);
};

#endif // TEXTDIALOG_H
