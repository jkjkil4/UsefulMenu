#include "screenshot.h"

#include "Area/areapoint.h"
#include "Area/horarea.h"
#include "Area/verarea.h"

#include "ButtonMenu/buttonmenu.h"

#include "ImgView/imgview.h"

#include "IconBtn/iconbtn.h"
#include "Line/line.h"


QString getLibName() {
    return "截图";
}

QPixmap getLibPixmap() {
    return QPixmap(":/Screenshot/Resource/Screenshot.png");
}

void Main(QWidget*) {
    QImage img = QApplication::primaryScreen()->grabWindow(0).toImage();
    QSettings config(APP_DIR + "/Config/Screenshot.ini", QSettings::IniFormat);

    if(config.value("config/hasWidget", true).toBool()) {
        Screenshot* screenshot = new Screenshot(img);
        screenshot->setAttribute(Qt::WA_DeleteOnClose, true);
        screenshot->exec();
    } else {
        QDir dir;
        if(!dir.exists(APP_DIR + "/Data/ScreenShot"))
            dir.mkpath(APP_DIR + "/Data/ScreenShot");
        Screenshot::saveImage(img, img.rect(), APP_DIR + "/Data/ScreenShot/" + Screenshot::getSaveFileName());
    }
}


static QAction actOpenDir("打开截图文件夹");

void appendAction(QMenu *menu) {
    menu->addSeparator();
    menu->addAction(&actOpenDir);
}

void checkAction(QAction *res) {
    if(res == &actOpenDir) {
        QDir dir;
        dir.mkpath(APP_DIR + "/Data/Screenshot");
        QProcess::startDetached("cmd.exe", QStringList() << "/c" << "start" << "" << APP_DIR + "/Data/Screenshot");
        //QProcess::startDetached("explorer.exe \"Data\\Screenshot\"");
    }
}



Screenshot::Screenshot(QImage &img)
    : img(img)
{
    //按钮菜单
    btnMenu = new ButtonMenu(this);
    btnMenu->setBgColor(QColor(230, 230, 230));
    btnMenu->setMargin(5);
    btnMenu->setSpcing(5);

    btnSave = new IconBtn(QIcon(":/ScreenshotBtn/Resource/save1.png"));
    connect(btnSave, SIGNAL(clicked()), this, SLOT(onBtnSavePressed()));
    addBtn(btnMenu, btnSave);

    IconBtn *btnSaveAs = new IconBtn(QIcon(":/ScreenshotBtn/Resource/save2.png"));
    connect(btnSaveAs, SIGNAL(clicked()), this, SLOT(onBtnSaveAsPressed()));
    addBtn(btnMenu, btnSaveAs);

    btnMenu->addWidget(new Line(Qt::Vertical));

    IconBtn *btnCancel = new IconBtn(QIcon(":/ScreenshotBtn/Resource/cancel.png"));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelPressed()));
    addBtn(btnMenu, btnCancel);

    IconBtn *btnAccept = new IconBtn(QIcon(":/ScreenshotBtn/Resource/accept.png"));
    connect(btnAccept, SIGNAL(clicked()), this, SLOT(onBtnAcceptPressed()));
    addBtn(btnMenu, btnAccept);

    btnMenu->adjustSize();


    //左侧的点
    areaWidgets.push_back(new HorArea(HorArea::Point, &area.x1, &area.y1, &area.y2, this));
    //右侧的点
    areaWidgets.push_back(new HorArea(HorArea::Point, &area.x2, &area.y1, &area.y2, this));
    //上方的点
    areaWidgets.push_back(new VerArea(VerArea::Point, &area.y1, &area.x1, &area.x2, this));
    //下方的点
    areaWidgets.push_back(new VerArea(VerArea::Point, &area.y2, &area.x1, &area.x2, this));

    //左侧的线
    areaWidgets.push_back(new HorArea(HorArea::Line, &area.x1, &area.y1, &area.y2, this));
    //右侧的线
    areaWidgets.push_back(new HorArea(HorArea::Line, &area.x2, &area.y1, &area.y2, this));
    //上方的线
    areaWidgets.push_back(new VerArea(VerArea::Line, &area.y1, &area.x1, &area.x2, this));
    //下方的线
    areaWidgets.push_back(new VerArea(VerArea::Line, &area.y2, &area.x1, &area.x2, this));

    //左上角
    areaPoints.push_back(new AreaPoint(&area.x1, &area.y1, this));
    //右上角
    areaPoints.push_back(new AreaPoint(&area.x2, &area.y1, this));
    //左下角
    areaPoints.push_back(new AreaPoint(&area.x1, &area.y2, this));
    //右下角
    areaPoints.push_back(new AreaPoint(&area.x2, &area.y2, this));

    for(auto point : areaPoints)
        areaWidgets.push_back(point);

    for(auto controler : areaWidgets) {
        controler->setVisible(false);
        connect(controler, SIGNAL(moved()), this, SLOT(onAreaChanged()));
        connect(controler, SIGNAL(released()), this, SLOT(onAreaChangeDone()));
    }
    onAreaChanged();

    changeArea->setSingleShot(true);
    connect(changeArea, SIGNAL(timeout()), this, SLOT(onChangeAreaTimeout()));


    //大图显示
    imgView = new ImgView(&img, this);


    //设置窗口属性
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::SubWindow | Qt::FramelessWindowHint);
    //全屏
    //showFullScreen();
    //设置大小
    resize(img.size());
    move(0, 0);
    //总是得到mouseMoveEvent
    setMouseTracking(true);
}

Screenshot::~Screenshot() {
    for(auto controler : areaWidgets)
        delete controler;
}

void Screenshot::addBtn(ButtonMenu *menu, IconBtn *btn) {
    btn->setColorNormal(QColor(220, 220, 220));
    btn->setColorMouseAt(QColor(230, 230, 230));
    btn->setColorHolding(QColor(210, 210, 210));
    btn->setMouseTracking(true);
    menu->addWidget(btn);
}


QCursor Screenshot::getCursorType(int flags) {
    int x = (flags & Qt::AlignLeft ? 0 : (flags & Qt::AlignRight ? 2 : 1));
    int y = (flags & Qt::AlignTop ? 0 : (flags & Qt::AlignBottom ? 2 : 1));
    return alignMap[x][y];
}


void Screenshot::onAreaChanged() {
    isAreaChanged = true;
    area.x1 = qBound(0, area.x1, img.width() - 1);
    area.x2 = qBound(0, area.x2, img.width() - 1);
    area.y1 = qBound(0, area.y1, img.height() - 1);
    area.y2 = qBound(0, area.y2, img.height() - 1);

    if(btnMenu->isVisible())
        btnMenu->myHide();

    AreaParent *pSender = (AreaParent*)sender();
    if(pSender)
        pSender->onOtherMoved();
    if(!changeArea->isActive())
        changeArea->start(8);
}
void Screenshot::onChangeAreaTimeout() {
    if(isAreaChanged) {
        for(auto point : areaWidgets)
            point->onOtherMoved();

        cutRect = area.rect();
    }

    if(imgView->isVisible()) {
        //得到控件应当移动至的坐标
        QPoint mousePos = cursor().pos();
        QPoint pos = mousePos + QPoint(ImgView::offset, ImgView::offset);

        //限制
        QSize screenSize = QApplication::primaryScreen()->size();
        if(pos.x() > screenSize.width() - imgView->width())
            pos.setX(pos.x() - imgView->width() - ImgView::offset * 2);
        if(pos.y() > screenSize.height() - imgView->height())
            pos.setY(pos.y() - imgView->height() - ImgView::offset * 2);

        //移动
        imgView->setFocusPos(mousePos);
        imgView->move(pos);
    }

    if(isAreaChanged) {
        isAreaChanged = false;
        update();
    }
}


QString Screenshot::getSaveFileName() {
    //"jss" means "jScreenShot"
    return "jss " + QDateTime(QDateTime::currentDateTime()).toString("yy-MM-dd hh-mm-ss-")
             + getMS() + ".png";
}

QString Screenshot::getMS() {
    QString ms = QString::number(QDateTime::currentDateTime().time().msec());
    for( int i = 0; i < 3 - ms.length(); i++ )
        ms.insert(0, "0");
    return ms;
}

void Screenshot::saveImage(const QImage &img, const QRect &rect, const QString &path, QWidget* boxParent) {
    if(!rect.isValid()) {
        QMessageBox::warning(boxParent, "错误", "图像无效");
        return;
    }
    if(!img.copy(rect).save(path)) {
        QMessageBox::warning(boxParent, "错误", "保存失败");
        return;
    }

    QMessageBox::information(boxParent, "提示", "保存成功");
}


void Screenshot::onAreaChangeDone() {
    int *left = (area.x1 < area.x2 ? &area.x1 : &area.x2);
    int *top = (area.y1 < area.y2 ? &area.y1 : &area.y2);

    for(auto point : areaPoints) {
        int flags = (point->pX == left ? Qt::AlignLeft : Qt::AlignRight);
        flags |= (point->pY == top ? Qt::AlignTop : Qt::AlignBottom);
        point->setCursor(getCursorType(flags));
    }
}


void Screenshot::onBtnSavePressed() {
    QDir dir;
    if(!dir.exists(APP_DIR + "/Data/ScreenShot"))
        dir.mkpath(APP_DIR + "/Data/ScreenShot");

    saveImage(img, cutRect, APP_DIR + "/Data/ScreenShot/" + getSaveFileName(), this);
}

void Screenshot::onBtnSaveAsPressed() {
    //打开ini文件
    QSettings config(APP_DIR + "/Config/Screenshot.ini", QSettings::IniFormat);
    //从ini中得到原先存储图片的路径
    QString pathBefore = config.value("path/saveImagePath", "").toString();
    //从用户处得到存储图片的路径
    QString path = QFileDialog::getSaveFileName(this, QString(), pathBefore + "/" + getSaveFileName(), "png (*.png);;jpg (*.jpg)");

    if(path != "") {    //如果路径不为空
        //将该路径保存至ini中
        config.setValue("path/saveImagePath", QFileInfo(path).path());
        //存储图片
        saveImage(img, cutRect, path, this);
    }
}

void Screenshot::onBtnCancelPressed() {
    close();
}

void Screenshot::onBtnAcceptPressed() {
    QApplication::clipboard()->setImage(img.copy(cutRect));
    close();
}


void Screenshot::setControlerVisible(bool on) {
    for(auto controler : areaWidgets)
        controler->setVisible(on);
}


void Screenshot::keyPressEvent(QKeyEvent *ev) {
    int xOffset = 0, yOffset = 0;
    switch (ev->key()) {
    case Qt::Key_W:
        yOffset = -1;
        break;
    case Qt::Key_S:
        yOffset = 1;
        break;
    case Qt::Key_A:
        xOffset = -1;
        break;
    case Qt::Key_D:
        xOffset = 1;
        break;
    }
    cursor().setPos(cursor().pos() + QPoint(xOffset, yOffset));

    QDialog::keyPressEvent(ev);
}


void Screenshot::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        if(isFirstMove) {
            QPoint pos = ev->pos();
            //设置区域的位置
            area.x1 = pos.x();
            area.y1 = pos.y();
            area.x2 = pos.x();
            area.y2 = pos.y();
            //显示
            onAreaChanged();
            onAreaChangeDone();
            setControlerVisible(true);
        }
        if(!btnMenu->isVisible())
            imgView->setVisible(true);
    }
}

void Screenshot::mouseMoveEvent(QMouseEvent *ev) {
    if(ev->buttons() & Qt::LeftButton) {
        if(isFirstMove) {
            QPoint pos = ev->pos();
            area.x2 = pos.x();
            area.y2 = pos.y();
            onAreaChanged();
        }
    }

    if(!changeArea->isActive())
        changeArea->start(8);
}

void Screenshot::mouseReleaseEvent(QMouseEvent *ev) {
    switch ((int)ev->button()) {
    case Qt::LeftButton:
        if(isFirstMove){
            isFirstMove = false;
        }
        btnMenu->myShow(QPoint(qMax(area.x1, area.x2), qMax(area.y1, area.y2)));
        imgView->setVisible(false);
        break;
    case Qt::RightButton:
        if(isFirstMove) {
            close();
        }
        break;
    }
}


void Screenshot::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.drawImage(0, 0, img);

    p.setPen(Qt::NoPen);
    p.setBrush(QColor(0, 0, 0, 128));

    QRegion region = QRegion(0, 0, width(), height()) - cutRect;

    for(auto rect : region)
        p.drawRect(rect);

}
