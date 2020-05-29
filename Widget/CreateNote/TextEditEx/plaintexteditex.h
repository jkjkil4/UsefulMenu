#ifndef TEXTEDITEX_H
#define TEXTEDITEX_H

#include <QPlainTextEdit>

#include <QWheelEvent>

class PlainTextEditEx : public QPlainTextEdit
{
    Q_OBJECT
protected:
    void wheelEvent(QWheelEvent *ev) override;

signals:
    void pointSizeChanged(int);

public:
    explicit PlainTextEditEx(QWidget *parent = nullptr);
    ~PlainTextEditEx() override = default;
};

#endif // TEXTEDITEX_H
