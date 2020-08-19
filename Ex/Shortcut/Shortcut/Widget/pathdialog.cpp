#include "pathdialog.h"

PathDialog::PathDialog()
{
    delayTimer->setSingleShot(true);
    connect(delayTimer, &QTimer::timeout, [=]{
        btnAccept->setText("确定");
        btnAccept->setStyleSheet("");
    });

    //创建控件
    QLineEdit *lineEdit = new QLineEdit;
    lineEdit->setMinimumWidth(250);
    QFont font = lineEdit->font();
    font.setPointSize(10);
    lineEdit->setFont(font);

    btnAccept = new QPushButton("确定");
    btnAccept->setMaximumWidth(60);
    connect(btnAccept, &QPushButton::clicked, [=]{
        QString str = lineEdit->text();
        if( str != "" ){
            QDir dir;
            if( dir.exists(str) && QDir(str).isAbsolute() ){
                path = str;
                close();
            }else{
                btnAccept->setText("无效路径");
                btnAccept->setStyleSheet("color:rgb(196,64,64);");
                delayTimer->start(2000);
            }
        }
    });

    btnCancel = new QPushButton("取消");
    btnCancel->setMaximumWidth(60);
    connect(btnCancel, &QPushButton::clicked, [=]{
        path = "";
        close();
    });


    //创建布局
    QHBoxLayout *layBtn = new QHBoxLayout;
    layBtn->addStretch();
    layBtn->addWidget(btnAccept);
    layBtn->addWidget(btnCancel);

    QVBoxLayout *layMain = new QVBoxLayout;
    layMain->addWidget(lineEdit);
    layMain->addLayout(layBtn);

    setLayout(layMain);


    //设置窗口属性
    setWindowTitle("添加路径");
    setWindowFlags(Qt::SubWindow | Qt::WindowStaysOnTopHint);
    adjustSize();
    setMinimumSize(width(), height());
    setMaximumSize(width(), height());
}
