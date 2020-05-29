#include "plaintexteditex.h"

PlainTextEditEx::PlainTextEditEx(QWidget *parent)
    : QPlainTextEdit(parent) {}


void PlainTextEditEx::wheelEvent(QWheelEvent *ev){
    if( ev->modifiers() & Qt::ControlModifier ){
        int angle = ev->angleDelta().y();
        int resAngle=font().pointSize()+angle/120;
        //限制
        resAngle = qBound(1, resAngle, 30);

        if( resAngle!=font().pointSize() ) {
            QFont resFont = QFont( font().family(), resAngle );
            setFont(resFont);

            emit pointSizeChanged(resAngle);
        }
        return;
    }
    QPlainTextEdit::wheelEvent(ev);
}
