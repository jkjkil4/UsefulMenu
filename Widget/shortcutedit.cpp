#include "shortcutedit.h"

ShortcutEdit::ShortcutEdit(QxtGlobalShortcut *shortcut, QWidget *parent)
    : QWidget(parent), shortcut(shortcut)
{
    setFocusPolicy(Qt::ClickFocus);
    shortcut->setEnabled(false);
}

ShortcutEdit::~ShortcutEdit() {
    shortcut->setEnabled();
}


struct Modifier_String {
    Qt::KeyboardModifier modifier;
    QString str;
};
struct KeyCheck {
    bool(*checkFunc)(int);
    void(*doFunc)(int, QString&);
};

void ShortcutEdit::keyPressEvent(QKeyEvent *ev) {
    if(!ev->isAutoRepeat()) {
        static QVector<Modifier_String> vModifiers = {
            {Qt::ControlModifier, "Ctrl"},
            {Qt::AltModifier, "Alt"},
            {Qt::ShiftModifier, "Shift"}
        };

        bool hasPrev = false;
        bool hasKey = false;
        QString result;

        Qt::KeyboardModifiers modifiers = ev->modifiers();
        for(auto& ms : vModifiers) {
            if(modifiers.testFlag(ms.modifier)) {
                if(hasPrev) result += '+';
                else hasPrev = true;

                result += ms.str;
            }
        }

        static QVector<KeyCheck> vKeyChecks = {
            {
                [](int key) -> bool { return key >= Qt::Key_A && key <= Qt::Key_Z; },
                [](int key, QString& res) { res += (char)('A' + (key - Qt::Key_A)); }
            },{
                [](int key) -> bool { return key >= Qt::Key_0 && key <= Qt::Key_9; },
                [](int key, QString& res) { res += (char)('0' + (key - Qt::Key_0)); }
            },{
                [](int key) -> bool { return key >= Qt::Key_F1 && key <= Qt::Key_F35; },
                [](int key, QString& res) { res += 'F' + QString::number(key - Qt::Key_F1 + 1); }
            }
        };

        int key = ev->key();
        for(auto& kc : vKeyChecks) {
            if((*kc.checkFunc)(key)) {
                if(hasPrev) result += '+';
                else hasPrev = true;

                hasKey = true;
                (*kc.doFunc)(key, result);
                break;
            }
        }

        if(hasKey) {
            QString prev = shortcut->shortcut().toString();
            if(!shortcut->setShortcut(QKeySequence(result))) {
                shortcut->setShortcut(QKeySequence(prev));
            } else update();
        }
    }
}

void ShortcutEdit::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setFont(font);

    QRect textRect(2, 2, width() - 4, height() - 4);

    p.fillRect(textRect, Qt::white);
    jDrawRecFrame(p, 0, 0, width(), height(), 2, hasFocus() ? QColor(70, 70, 220) : Qt::black);
    p.drawText(textRect, Qt::AlignCenter | Qt::AlignVCenter, shortcut->shortcut().toString());
}
