#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsEllipseItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    labViewCord = new QLabel("View 坐标：");
    labViewCord->setMinimumWidth(150);
    ui->statusBar->addWidget(labViewCord);

    labSceneCord = new QLabel("Scene 坐标：");
    labSceneCord->setMinimumWidth(150);
    ui->statusBar->addWidget(labSceneCord);

    labItemCord = new QLabel("Item 坐标：");
    labItemCord->setMinimumWidth(150);
    ui->statusBar->addWidget(labItemCord);

    ui->View->setCursor(Qt::CrossCursor);
    ui->View->setMouseTracking(true);
    ui->View->setDragMode(QGraphicsView::RubberBandDrag);

    QObject::connect(ui->View, SIGNAL(mouseMovePoint(QPoint)),
                     this, SLOT(on_mouseMovePoint(QPoint)));
    QObject::connect(ui->View, SIGNAL(mouseClicked(QPoint)),
                     this, SLOT(on_mouseClicked(QPoint)));

    iniGraphicsSystem();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 窗口变化大小时的事件
void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    // Graphics View 坐标，左上角总是(0, 0)，宽度=，长度=
    ui->LabViewSize->setText(QString::asprintf("Graphics view坐标，左上角总是(0, 0)，宽度=%d，高度=%d",
                             ui->View->width(), ui->View->height()));
    QRectF rectF = ui->View->sceneRect(); // Scene的矩形区
    ui->LabSceneRect->setText(QString::asprintf("QGraphicsView::sceneRect=(Left,Top,Width,Height)=%.0f,%.0f,%.0f,%0.f",
                            rectF.left(), rectF.top(), rectF.width(), rectF.height()));
}

// 构造Graphics View的各项
void MainWindow::iniGraphicsSystem()
{
    QRectF rect(-200, -100, 400, 200);
    scene = new QGraphicsScene(rect); // scene逻辑坐标系定义
    ui->View->setScene(scene);

    // 画一个矩形框，大小等于scene
    QGraphicsRectItem *item = new QGraphicsRectItem(rect);
    item->setFlags(QGraphicsItem::ItemIsSelectable
                   |QGraphicsItem::ItemIsFocusable);
    QPen pen;
    pen.setWidth(2);
    item->setPen(pen);
    scene->addItem(item);

    // 一个位于scene中心的椭圆，测试局部坐标
    QGraphicsEllipseItem *item2 = new QGraphicsEllipseItem(-100,-50,200,100);
    item2->setPos(0, 0);
    item2->setBrush(QBrush(Qt::blue));
    item2->setFlags(QGraphicsItem::ItemIsMovable|
                    QGraphicsItem::ItemIsSelectable|
                    QGraphicsItem::ItemIsFocusable);
    scene->addItem(item2);

    // 一个圆，中心位于scene的边缘
    QGraphicsEllipseItem *item3 = new QGraphicsEllipseItem(-50, -50, 100, 100);
    item3->setPos(rect.right(), rect.bottom());
    item3->setBrush(QBrush(Qt::red));
    item3->setFlags(QGraphicsItem::ItemIsMovable|
                    QGraphicsItem::ItemIsSelectable|
                    QGraphicsItem::ItemIsFocusable);
    scene->addItem(item3);

    scene->clearSelection();
}

// 鼠标移动事件，point是GraphicsView的坐标，物理坐标
void MainWindow::on_mouseMovePoint(QPoint point)
{
    labViewCord->setText(QString::asprintf("View 坐标：%d,%d", point.x(), point.y()));
    QPointF pointScene = ui->View->mapToScene(point);	// 转换到Scene坐标
    labSceneCord->setText(QString::asprintf("Scene坐标：%.0f,%.0f", pointScene.x(), pointScene.y()));
}

// 鼠标单击事件
void MainWindow::on_mouseClicked(QPoint point)
{
    QPointF pointScene = ui->View->mapToScene(point);	// 转换到Scene坐标
    QGraphicsItem *item = nullptr;
    item = scene->itemAt(pointScene, ui->View->transform());	// 获取光标下的绘图项
    if (item != nullptr) {	// 有绘图项
        QPointF pointItem = item->mapFromScene(pointScene);	// 转换为绘图项的局部坐标
        labItemCord->setText(QString::asprintf("Item坐标：%.0f,%.0f", pointItem.x(), pointItem.y()));
    }
}
