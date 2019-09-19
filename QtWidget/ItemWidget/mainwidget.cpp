#include "mainwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>
#include <QGroupBox>
#include <cmath>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    angle = 0;
    scaleValue = 5;
    shearValue = 5;
    translateValue = 50;

    QGraphicsScene *scene = new QGraphicsScene;
    // 限定新建 QgraphicsScene 对象的显示区域
    scene->setSceneRect(-200, -200, 400, 400);

    QPixmap *pixmap = new QPixmap("image.png");
    pixItem = new PixItem(pixmap);
    scene->addItem(pixItem);
    pixItem->setPos(0, 0);

    view = new QGraphicsView;	// 新建一个视图对象
    view->setScene(scene);	// 将视图对象与场景相连
    view->setMinimumSize(400, 400);

    ctrlFrame = new QFrame;
    createControlFrame();	// 新建主窗口右侧的控制面板区

    // 主窗口布局
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(10);
    mainLayout->setSpacing(20);
    mainLayout->addWidget(view);
    mainLayout->addWidget(ctrlFrame);
    setLayout(mainLayout);
    setWindowTitle(tr("Graphics Item Transfromation"));
}

MainWidget::~MainWidget()
{

}

// 创建右侧的控制面板，旋转、缩放、切变、位移等控制区，每个控制区由包含QSlider对象的QGroupBox对象实现
void MainWidget::createControlFrame()
{
    // 旋转控制
    QSlider *rotateSlider = new QSlider;
    rotateSlider->setOrientation(Qt::Horizontal);
    rotateSlider->setRange(0, 360);
    QHBoxLayout *rotateLayout = new QHBoxLayout;
    rotateLayout->addWidget(rotateSlider);
    QGroupBox *rotateGroup = new QGroupBox(tr("Rotate"));
    rotateGroup->setLayout(rotateLayout);

    // 缩放控制
    QSlider *scaleSlider = new QSlider;
    scaleSlider->setOrientation(Qt::Horizontal);
    scaleSlider->setRange(0, 2*scaleValue);
    scaleSlider->setValue(scaleValue);
    QHBoxLayout *scaleLayout = new QHBoxLayout;
    scaleLayout->addWidget(scaleSlider);
    QGroupBox *scaleGroup = new QGroupBox(tr("Scale"));
    scaleGroup->setLayout(scaleLayout);

    // 切变控制
    QSlider *shearSlider = new QSlider;
    shearSlider->setOrientation(Qt::Horizontal);
    shearSlider->setRange(0, 2*shearValue);
    shearSlider->setValue(shearValue);
    QHBoxLayout *shearLayout = new QHBoxLayout;
    shearLayout->addWidget(shearSlider);
    QGroupBox *shearGroup = new QGroupBox(tr("Shear"));
    shearGroup->setLayout(shearLayout);

    // 位移控制
    QSlider *translateSlider = new QSlider;
    translateSlider->setOrientation(Qt::Horizontal);
    translateSlider->setRange(0, 2*translateValue);
    translateSlider->setValue(translateValue);
    QHBoxLayout *translateLayout = new QHBoxLayout;
    translateLayout->addWidget(translateSlider);
    QGroupBox *translateGroup = new QGroupBox(tr("Translate"));
    translateGroup->setLayout(translateLayout);

    // 连接信号槽
    connect(rotateSlider, SIGNAL(valueChanged(int)), this, SLOT(slotRotate(int)));
    connect(scaleSlider, SIGNAL(valueChanged(int)), this, SLOT(slotScale(int)));
    connect(shearSlider, SIGNAL(valueChanged(int)), this, SLOT(slotShear(int)));
    connect(translateSlider, SIGNAL(valueChanged(int)), this, SLOT(slotTranslate(int)));

    // 控制面板布局
    QVBoxLayout *frameLayout = new QVBoxLayout;
    frameLayout->setMargin(10);
    frameLayout->setSpacing(20);
    frameLayout->addWidget(rotateGroup);
    frameLayout->addWidget(scaleGroup);
    frameLayout->addWidget(shearGroup);
    frameLayout->addWidget(translateGroup);
    ctrlFrame->setLayout(frameLayout);
}

// 图元的旋转功能
void MainWidget::slotRotate(int value)
{
    view->rotate(value - angle);
    angle = value;
}

// 图元的缩放功能
void MainWidget::slotScale(int value)
{
    qreal s;
    if (value > scaleValue) {
        s = pow(1.1, (value - scaleValue));
    } else {
        s = pow(1/1.1, (scaleValue - value));
    }
    view->scale(s, s);
    scaleValue = value;
}

// 图元的切变功能
void MainWidget::slotShear(int value)
{
    view->shear((value - shearValue)/10.0, 0);
    shearValue = value;
}

// 图元的位移功能
void MainWidget::slotTranslate(int value)
{
    view->translate(value - translateValue, value - translateValue);
    translateValue = value;
}
