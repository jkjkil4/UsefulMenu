#include "pathdialog.h"

#include <QDebug>

PathDialog::PathDialog(QWidget *parent) : QDialog(parent)
{
    delayTimer->setSingleShot(true);
    connect( delayTimer, &QTimer::timeout, [=]() {
        btnAccept->setText("确定");
        btnAccept->setStyleSheet("");
    }
    );

    btnAccept->setMaximumWidth(60);
    btnCancel->setMaximumWidth(60);
    connect( btnAccept, &QPushButton::clicked, [=]() {
        QString str = lineEdit->text();
        if( str != "" ){
            QDir dir;
            if( dir.exists(str) && QDir(str).isAbsolute() ){
                emit accepted();
                onHide();
            }else{
                btnAccept->setText("无效路径");
                btnAccept->setStyleSheet("color:rgb(196,64,64);");
                delayTimer->start(2000);
            }
        }
    }
    );
    connect( btnCancel, &QPushButton::clicked,[=]() {
        onHide();
    });

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing(4);
    layout->setMargin(4);
    layout->addWidget(lineEdit);
    layout->addWidget(btnAccept);
    layout->addWidget(btnCancel);
    setLayout(layout);
}


QString PathDialog::text(){
    return lineEdit->text();
}


void PathDialog::onHide() {
    setVisible(false);
    lineEdit->setText("");
    btnAccept->setText("确定");
    btnAccept->setStyleSheet("");
    emit hided();
}


void PathDialog::setFocusToLineEdit() {
    lineEdit->setFocus();
}
