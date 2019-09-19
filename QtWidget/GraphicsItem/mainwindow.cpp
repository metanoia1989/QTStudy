#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenus();
    scene = new QGraphicsScene;
    scene->setSceneRect(-200, -200, 400, 400);
    initScene();	// 初始化场景
    QGraphicsView *view = new QGraphicsView;
    view->setScene(scene);
    view->setMinimumSize(400, 400);
    view->show();
    setCentralWidget(view);
    resize(550, 450);
    setWindowTitle(tr("Graphics Items"));
}

MainWindow::~MainWindow()
{

}

// 创建动作
void MainWindow::createActions()
{
    newAct = new QAction(tr("新建"), this);
    clearAct = new QAction(tr("清除"), this);
    exitAct = new QAction(tr("退出"), this);
    addEllipseItemAct = new QAction(tr("加入 椭圆"), this);
    addPolygonItemAct = new QAction(tr("加入 多边形"), this);
    addTextItemAct = new QAction(tr("加入 文字"), this);
    addRectItemAct = new QAction(tr("加入 长方形"), this);
    addAlphaItemAct = new QAction(tr("加入 透明图片"), this);
    connect(newAct, SIGNAL(triggered()), this, SLOT(slotNew()));
    connect(clearAct, SIGNAL(triggered()), this, SLOT(slotClear()));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
    connect(addEllipseItemAct, SIGNAL(triggered()), this, SLOT(slotAddEllipseItem()));
    connect(addPolygonItemAct, SIGNAL(triggered()), this, SLOT(slotAddPolygonItem()));
    connect(addTextItemAct, SIGNAL(triggered()), this, SLOT(slotAddTextItem()));
    connect(addRectItemAct, SIGNAL(triggered()), this, SLOT(slotAddRectItem()));
    connect(addAlphaItemAct, SIGNAL(triggered()), this, SLOT(slotAddAlphaItem()));
}

// 创建菜单
void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("文件"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(clearAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
    QMenu *itemsMenu = menuBar()->addMenu(tr("元素"));
    itemsMenu->addAction(addEllipseItemAct);
    itemsMenu->addAction(addPolygonItemAct);
    itemsMenu->addAction(addTextItemAct);
    itemsMenu->addAction(addRectItemAct);
    itemsMenu->addAction(addAlphaItemAct);
}

// 初始化场景
void MainWindow::initScene()
{
    int i;
    for (i=0;i<3;i++) {
        slotAddEllipseItem();
    }
    for (i=0;i<3;i++) {
        slotAddTextItem();
    }
    for (i=0;i<3;i++) {
        slotAddRectItem();
    }
    for (i=0;i<3;i++) {
        slotAddAlphaItem();
    }
}

// 新建一个显示窗体
void MainWindow::slotNew()
{
    slotClear();
    initScene();
    MainWindow *newWin = new MainWindow;
    newWin->show();
}

// 清除场景中所有的图元
void MainWindow::slotClear()
{
    QList<QGraphicsItem*> listItem = scene->items();
    while (!listItem.empty()) {
        scene->removeItem(listItem.at(0));
        listItem.removeAt(0);
    }
}

// 在场景中加入一个椭圆形图元
void MainWindow::slotAddEllipseItem()
{
    QGraphicsEllipseItem *item = new QGraphicsEllipseItem(QRectF(0, 0, 80, 60));
    item->setPen(Qt::NoPen);
    item->setBrush(QColor(qrand()%256, qrand()%256, qrand()%256));
    item->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(item);
    item->setPos((qrand()%int(scene->sceneRect().width()))-200,
        (qrand()%int(scene->sceneRect().height()))-200);
}

// 在场景中加入一个多边形图元
void MainWindow::slotAddPolygonItem()
{
    QVector<QPoint> v;
    v << QPoint(30, -15) << QPoint(0, -30) << QPoint(-30, -15)
      << QPoint(-30, -15) << QPoint(0, 30) << QPoint(30, 15);
    QGraphicsPolygonItem *item = new QGraphicsPolygonItem(QPolygonF(v));
    item->setBrush(QColor(qrand()%256, qrand()%256, qrand()%256));
    item->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(item);
    item->setPos((qrand()%int(scene->sceneRect().width()))-200,
        (qrand()%int(scene->sceneRect().height()))-200);

}

// 在场景中加入一个文字图元
void MainWindow::slotAddTextItem()
{
    QFont font("Times", 16);
    QGraphicsTextItem *item = new QGraphicsTextItem("Hello Qt");
    item->setFont(font);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setDefaultTextColor(QColor(qrand()%256, qrand()%256, qrand()%256));
    scene->addItem(item);
    item->setPos((qrand()%int(scene->sceneRect().width()))-200,
        (qrand()%int(scene->sceneRect().height()))-200);
}

// 在场景中加入一个长方形图元
void MainWindow::slotAddRectItem()
{
    QGraphicsRectItem *item = new QGraphicsRectItem(QRectF(0, 0, 60, 60));
    QPen pen;
    pen.setWidth(3);
    pen.setColor(QColor(qrand()%256, qrand()%256, qrand()%256));
    item->setPen(Qt::NoPen);
    item->setBrush(QColor(qrand()%256, qrand()%256, qrand()%256));
    item->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(item);
    item->setPos((qrand()%int(scene->sceneRect().width()))-200,
        (qrand()%int(scene->sceneRect().height()))-200);
}

// 在场景中加入一个透明蝴蝶图片
void MainWindow::slotAddAlphaItem()
{

    QGraphicsPixmapItem *item = scene->addPixmap(QPixmap("image.png"));
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setPos((qrand()%int(scene->sceneRect().width()))-200,
        (qrand()%int(scene->sceneRect().height()))-200);
}
