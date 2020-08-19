#ifndef BUTTONTABLE_H
#define BUTTONTABLE_H


#include <QWidget>
#include <QMenu>

#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>
#include <QToolTip>

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

    virtual QString tooltipText() { return ""; }
};


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

    void moveItem(int index, int toIndex);

    void addItem(ButtonTableItem* item);
    void removeItem(ButtonTableItem* item);
    void clearItem();

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

    QVector<ButtonTableItem*> vItems;

signals:
    void clicked(ButtonTableItem*);
    void itemMoved(ButtonTableItem*, ButtonTableItem*);

    void appendAction(QMenu*, ButtonTableItem*);
    void checkAction(QAction*, ButtonTableItem*);

private slots:
    void onTimerUpdateOffset();
    void onTimerCheckMouseOut();

    void onShowTooltip();

private:
    int btnWidth = 64;
    int btnHeight = 64;
    int btnXCount = 4;
    int spacing = 3;
    int margin = 3;

    QTimer *timerTooltip = new QTimer(this);
    void setMouseIndex(int index);
    void updateMouseIndexByMousePos();
    int mouseIndex = -1;
    bool isHolding = false;
    bool hasMenu = false;

    void startTimerUpdateOffset();
    QTimer* timerUpdateOffset = new QTimer(this);
    int spd = 0;
    int yOffset = 0;

    QTimer* timerCheckMouseOut = new QTimer(this);

    void startTimerUpdate();
    QTimer* timerUpdate = new QTimer(this);
    static constexpr int timerDelayMs = 8;
};

#endif // BUTTONTABLE_H
