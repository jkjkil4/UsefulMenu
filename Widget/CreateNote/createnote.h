#ifndef CREATENOTE_H
#define CREATENOTE_H

#include "Class/autoclosewidget.h"

#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QTextBlock>

#include <QMessageBox>
#include <QSettings>
#include <QDir>
#include <QDateTime>

#include "Class/global.h"

#include "TextEditEx/plaintexteditex.h"

class CreateNote : public AutoCloseWidget
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *ev) override;

public:
    explicit CreateNote(QWidget *parent = nullptr);
    ~CreateNote() override = default;

    QString makeTitleText();

public slots:
    void onTextEditPointSizeChanged();
    void onTextEditTextChanged();

    void onAutoWarpCheckBoxStateChanged(int state);
    void onKeepWindowCheckBoxStateChanged(int state);

    void onAcceptBtnClicked();
    void onCancelBtnClicked();

private:
    template<typename T>
    inline void setTextEditPointSize(T *edit, int pointSize);

    //该控件的标题
    QLabel *labTitle = new QLabel;

    //是否自动换行的勾选框
    QCheckBox *autoWarpCheckBox = new QCheckBox("自动换行");
    //是否固定窗口的勾选框
    QCheckBox *keepWindowCheckBox = new QCheckBox("固定窗口");

    //编辑标题
    QLineEdit *titleEdit = new QLineEdit;

    //编辑文本
    PlainTextEditEx *textEdit = new PlainTextEditEx;

    //确认和取消按钮
    QPushButton *btnAccept = new QPushButton("保存");
    QPushButton *btnCancel = new QPushButton("取消");

    //是否固定窗口
    bool isKeepWindow = true;
    bool isCloseByBtn = false;//是否是由于通过按钮关闭的窗口

};

#endif // CREATENOTE_H
