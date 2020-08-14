#include "stateball.h"


QString getLibName() {
    return "性能显示";
}

QPixmap getLibPixmap() {
    return QPixmap(":/StateBall/Resource/StateBall.png");
}


static bool isJQCPUMonitorInited = false;
static StateBall* curStateBall = nullptr;

void Main(QWidget*) {
    if(!isJQCPUMonitorInited) {
        isJQCPUMonitorInited = true;
        JQCPUMonitor::initialize();
    }

    if(curStateBall) {
        curStateBall->close();
        curStateBall = nullptr;
    }
    curStateBall = new StateBall;
    curStateBall->setVisible(true);
}


StateBall::StateBall(QWidget *parent) : QWidget(parent)
{
    //限制大小
    setMaximumSize(32, 32);
    setMinimumSize(32, 32);
    setCursor(Qt::PointingHandCursor);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::SubWindow);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setAttribute(Qt::WA_TranslucentBackground, true);

    //开始定时器
    timerGetState->start(1000);
    connect(timerGetState, SIGNAL(timeout()), this, SLOT(onGetState()));
}


void StateBall::onGetState() {
    //得到CPU使用率
    cpuUsage = JQCPUMonitor::cpuUsagePercentage();
    cpuArc = (int)(cpuUsage * 2880);

    //得到内存使用率
    ramUsage = getRAMUsage();
    ramArc = (int)(ramUsage * 2880);

    //更新
    update();
}

void StateBall::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        mousePosStart = ev->pos();
    }
}

void StateBall::mouseMoveEvent(QMouseEvent *ev) {
    if(ev->buttons() & Qt::LeftButton) {
        QPoint mousePos = ev->pos();
        int xOffset = mousePos.x() - mousePosStart.x();
        int yOffset = mousePos.y() - mousePosStart.y();
        int toX = x() + xOffset;
        int toY = y() + yOffset;
        QSize wndSize = QGuiApplication::primaryScreen()->availableSize();
        move(qBound(0, toX, wndSize.width() - width()),
             qBound(0, toY, wndSize.height() - height()));
    }
    ev->ignore();
}

void StateBall::mouseReleaseEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::RightButton) {
        QAction actClose("关闭");

        QMenu menu;
        menu.addAction(&actClose);

        menu.move(cursor().pos() + QPoint(3, 3));
        QAction* res = menu.exec();

        if(res == &actClose) {
            curStateBall = nullptr;
            close();
        }
    }
}

void StateBall::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    //绘制圆
    p.setBrush(QColor(230, 230, 230));
    p.setPen(QColor(190, 190, 190));
    p.drawEllipse(1, 1, 30, 30);

    //绘制圆弧
      //CPU
    p.setPen(QPen(QColor(100, 100, 255), 3));
    p.setClipRect(0, 0, 15, 32);
    p.drawArc(5, 5, 22, 22, 4320, -cpuArc);
      //CPU-Gray
    p.setPen(QPen(QColor(200, 200, 200), 3));
    p.drawArc(5, 5, 22, 22, 1440, 2880 - cpuArc);
      //RAM
    p.setPen(QPen(QColor(255, 100, 255), 3));
    p.setClipRect(17, 0, 15, 32);
    p.drawArc(5, 5, 22, 22, -1440, ramArc);
      //RAM-Gray
    p.setPen(QPen(QColor(200, 200, 200), 3));
    p.drawArc(5, 5, 22, 22, 1440, ramArc - 2880);
}
