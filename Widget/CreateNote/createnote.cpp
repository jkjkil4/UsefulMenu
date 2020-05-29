#include "createnote.h"


#define LIMIT_LENGTH 15
#define PLACEHOLDER_MAX_LENGTH 50

#include <QDebug>

CreateNote::CreateNote(QWidget *parent)
    : AutoCloseWidget(parent)
{
    QSettings config("settings.ini", QSettings::IniFormat);
    int pointSize = config.value("CreateNote/pointSize", 10).toInt();
    bool isAutoWarp = config.value("CreateNote/isAutoWarp", false).toBool();
    isKeepWindow = config.value("CreateNote/isKeepWindow", true).toBool();

    autoWarpCheckBox->setChecked(isAutoWarp);
    connect(autoWarpCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onAutoWarpCheckBoxStateChanged(int)));

    keepWindowCheckBox->setChecked(isKeepWindow);
    keepWindowCheckBox->setToolTip("固定窗口\n若勾选，不会因为失去焦点而消失");
    connect(keepWindowCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onKeepWindowCheckBoxStateChanged(int)));


    titleEdit->setPlaceholderText("标题");  //设置titleEdit的默认文字
    textEdit->setLineWrapMode(((QPlainTextEdit::LineWrapMode)isAutoWarp));  //设置是否自动换行
    textEdit->setWordWrapMode(QTextOption::WrapAnywhere);
    setTextEditPointSize(titleEdit, 11);    //设置titleEdit的字体大小
    setTextEditPointSize(textEdit, pointSize);  //设置textEdit的字体大小
    labTitle->setText(makeTitleText()); //设置该控件的顶端的文字
    connect(textEdit, SIGNAL(pointSizeChanged(int)), this, SLOT(onTextEditPointSizeChanged()));
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(onTextEditTextChanged()));


    connect(btnAccept, SIGNAL(clicked()), this, SLOT(onAcceptBtnClicked()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(onCancelBtnClicked()));


    QHBoxLayout *layTitle = new QHBoxLayout;
    layTitle->setSpacing(4);
    layTitle->setMargin(0);
    layTitle->addWidget(labTitle);
    layTitle->addStretch();
    layTitle->addWidget(autoWarpCheckBox);
    layTitle->addWidget(keepWindowCheckBox);


    QHBoxLayout *layEditTitle = new QHBoxLayout;
    layEditTitle->setSpacing(4);
    layEditTitle->setMargin(0);
    layEditTitle->addWidget(titleEdit);


    QHBoxLayout *layBottom = new QHBoxLayout;
    layBottom->setSpacing(4);
    layBottom->setMargin(0);
    layBottom->addStretch();
    layBottom->addWidget(btnAccept);
    layBottom->addWidget(btnCancel);


    QVBoxLayout *layMain = new QVBoxLayout;
    layMain->setSpacing(4);
    layMain->setMargin(4);
    layMain->addLayout(layTitle);
    layMain->addLayout(layEditTitle);
    layMain->addWidget(textEdit);
    layMain->addLayout(layBottom);
    setLayout(layMain);


    //设置属性
    setObjectName("CreateNote");
    setStyleSheet("#CreateNote{background-color: rgb(220, 220, 220);}");
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_DeleteOnClose);
    limitSize(this, 400, 300);
    adjustSize();

}


QString CreateNote::makeTitleText() {
    return "字体大小:" + QString::number(textEdit->font().pointSize());
}


void CreateNote::onTextEditPointSizeChanged() {
    labTitle->setText(makeTitleText());
}

void CreateNote::onTextEditTextChanged() {
    QString firstLine = textEdit->document()->firstBlock().text();
    titleEdit->setPlaceholderText(firstLine.left(PLACEHOLDER_MAX_LENGTH));
}


void CreateNote::onAutoWarpCheckBoxStateChanged(int state) {
    textEdit->setLineWrapMode((QPlainTextEdit::LineWrapMode)state);
}

void CreateNote::onKeepWindowCheckBoxStateChanged(int state) {
    isKeepWindow = state;
}


void CreateNote::onAcceptBtnClicked() {
    QString title = titleEdit->text();  //得到输入的文本
    if(title == "") //如果输入的文本为空(没输入)
        title = titleEdit->placeholderText();   //得到默认的文本

    //得到当前时间
    QString ms = QString::number(QDateTime::currentDateTime().time().msec());
    for( int i = 0; i < 3 - ms.length(); i++ )
        ms.insert(0, "0");
    QString timeStr = QDateTime(QDateTime::currentDateTime()).toString("yy-MM-dd hh-mm-ss-") + ms;

    //创建一些目录
    QDir dir;
    if(!dir.exists("Notes"))
        dir.mkdir("Notes");

    QString fileDirPath = "Notes/" + timeStr;
    if(!dir.exists(fileDirPath))
        dir.mkdir(fileDirPath);

    //保存设定
    QSettings noteConfig(fileDirPath + "/info.ini", QSettings::IniFormat);
    noteConfig.setValue("note/title", title);

    //保存文本
    QFile fileDoc(fileDirPath + "/doc.txt");
    if(fileDoc.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&fileDoc);
        out << textEdit->toPlainText();
        fileDoc.close();
    }

    //关闭窗口
    isCloseByBtn = true;
    close();
}

void CreateNote::onCancelBtnClicked() {
    isCloseByBtn = true;
    close();
}


void CreateNote::closeEvent(QCloseEvent *ev) {
    if(isKeepWindow && !isCloseByBtn) {
        ev->ignore();
        return;
    }

    //保存设定
    QSettings config("settings.ini", QSettings::IniFormat);
    config.setValue("CreateNote/pointSize", textEdit->font().pointSize());   //字符大小
    config.setValue("CreateNote/isAutoWarp", textEdit->lineWrapMode());   //是否自动换行
    config.setValue("CreateNote/isKeepWindow", isKeepWindow); //是否固定窗口
}


template<typename T>
inline void CreateNote::setTextEditPointSize(T *edit, int pointSize) {
    QFont font = edit->font();
    font.setPointSize(pointSize);
    edit->setFont(font);
}

