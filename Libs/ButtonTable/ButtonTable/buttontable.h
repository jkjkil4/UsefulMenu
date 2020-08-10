#ifndef BUTTONTABLE_H
#define BUTTONTABLE_H


#include <QWidget>

#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>

class ButtonTableItem
{
public:
    virtual ~ButtonTableItem() = default;

    enum class ButtonFlag { None, MouseAt, MouseHolding };

    virtual void onPaint(QPainter& p, QRect r, ButtonFlag flag) {
        QColor dwColor;
        switch(flag) {
        case ButtonFlag::None:
            dwColor = QColor(96, 192, 96);
            break;
        case ButtonFlag::MouseAt:
            dwColor = QColor(96, 96, 192);
            break;
        case ButtonFlag::MouseHolding:
            dwColor = QColor(192, 96, 96);
            break;
        }
        p.fillRect(r, dwColor);
    }
};
//Q_DECLARE_METATYPE(ButtonTableItem);
//#define DEC_BUTTONTABLEITEM_METATYPE qRegisterMetaType<ButtonTableItem>("ButtonTableItem");

class ButtonTable : public QWidget
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent* ev) override;
    void mouseMoveEvent(QMouseEvent* ev) override;
    void mouseReleaseEvent(QMouseEvent* ev) override;
    void wheelEvent(QWheelEvent* ev) override;
    void paintEvent(QPaintEvent*) override;

public:
    explicit ButtonTable(QWidget *parent = nullptr);
    ~ButtonTable() override;

    void adjustWidth();

    void addItem(ButtonTableItem* item);

    int getIndex(QPoint mouse);

    int getBtnWidth() const;
    void setBtnWidth(int value);

    int getBtnHeight() const;
    void setBtnHeight(int value);

    int getBtnXCount() const;
    void setBtnXCount(int value);

    int getSpacing() const;
    void setSpacing(int value);

    int getMargin() const;
    void setMargin(int value);

signals:
    void clicked(void*);

private slots:
    void onTimerUpdateOffset();
    void onTimerCheckMouseOut();

private:
    int btnWidth = 64;
    int btnHeight = 64;
    int btnXCount = 4;
    int spacing = 3;
    int margin = 3;

    QVector<ButtonTableItem*> vItems;

    int mouseIndex = -1;
    bool isHolding = false;

    QTimer* timerUpdateOffset = new QTimer(this);
    int spd = 0;
    int yOffset = 0;

    QTimer* timerCheckMouseOut = new QTimer(this);

    void startTimerUpdate();
    QTimer* timerUpdate = new QTimer(this);
    static constexpr int timerDelayMs = 8;
};

#endif // BUTTONTABLE_H
