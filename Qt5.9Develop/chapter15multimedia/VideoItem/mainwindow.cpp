#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this); // 创建视频播放器
    player->setNotifyInterval(2000); // 信息更新周期

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    videoItem = new QGraphicsVideoItem;
    videoItem->setSize(QSizeF(360, 240));
    videoItem->setFlags(QGraphicsItem::ItemIsMovable
                        |QGraphicsItem::ItemIsSelectable
                        |QGraphicsItem::ItemIsFocusable);
    scene->addItem(videoItem);
    player->setVideoOutput(videoItem); // 设置视频显示图形组件

    connect(player, &QMediaPlayer::stateChanged,
            this, &MainWindow::onstateChanged);
    connect(player, &QMediaPlayer::positionChanged,
            this, &MainWindow::onPositionChanged);
    connect(player, &QMediaPlayer::durationChanged,
            this, &MainWindow::onDurationChanged);

    // 矩形框内创建椭圆，绘图项的局部坐标，左上角(-100, -50)，宽200，高100
    QGraphicsEllipseItem *item2 = new QGraphicsEllipseItem(0, 0, 100, 50);
    item2->setPos(0, 0);
    item2->setBrush(QBrush(Qt::blue));
    item2->setFlags(QGraphicsItem::ItemIsMovable
                        |QGraphicsItem::ItemIsSelectable
                        |QGraphicsItem::ItemIsFocusable);
    scene->addItem(item2);

    // 矩形框内创建椭圆，绘图项的局部坐标，左上角没(-100, -50)
    // 一个圆，中心位于scene的边缘
    QGraphicsEllipseItem *item3 = new QGraphicsEllipseItem(50, 50, 50, 50);
    item3->setPos(100, 100);
    item3->setBrush(QBrush(Qt::red));
    item3->setFlags(QGraphicsItem::ItemIsMovable
                        |QGraphicsItem::ItemIsSelectable
                        |QGraphicsItem::ItemIsFocusable);
    scene->addItem(item3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 播放器状态变化
void MainWindow::onstateChanged(QMediaPlayer::State state)
{
    ui->btnPlay->setEnabled(!(state==QMediaPlayer::PlayingState));
    ui->btnPause->setEnabled(state==QMediaPlayer::PlayingState);
    ui->btnStop->setEnabled(state==QMediaPlayer::PlayingState);
}

// 文件时长变化
void MainWindow::onDurationChanged(qint64 duration)
{
    ui->sliderPosition->setMaximum(duration);
    int secs = duration / 1000; // 秒
    int mins = secs / 60; // 分钟
    secs = secs % 60; // 余秒数
    durationTime = QString::asprintf("%d:%d", mins, secs);
    ui->LabRatio->setText(positionTime + "/" + durationTime);
}

// 文件播放位置变化
void MainWindow::onPositionChanged(qint64 position)
{
    if (ui->sliderPosition->isSliderDown()) {
        return; // 如果正在拖动滑条
    }
    ui->sliderPosition->setSliderPosition(position);
    int secs = position / 1000; // 秒
    int mins = secs / 60; // 分钟
    secs = secs % 60; // 余数秒
    positionTime = QString::asprintf("%d:%d", mins, secs);
    ui->LabRatio->setText(positionTime + "/" + durationTime);
}

// 打开文件
void MainWindow::on_btnAdd_clicked()
{
    QString curPath = QDir::homePath(); // 获取系统当前目录
    QString dlgTitle = "选择视频文件"; // 对话框标题
    QString filter = "wmv文件(.*wmv);;mp4文件(*.mp4);;所有文件(*.*)";
    QString aFile = QFileDialog::getOpenFileName(this,
                     dlgTitle, curPath, filter);
    if (aFile.isEmpty()) return;
    QFileInfo fileInfo(aFile);
    ui->LabCurMedia->setText(fileInfo.fileName());

    player->setMedia(QUrl::fromLocalFile(aFile)); // 设置播放文件
    player->play();
}

// 播放
void MainWindow::on_btnPlay_clicked()
{
    player->play();
}

// 暂停
void MainWindow::on_btnPause_clicked()
{
    player->pause();
}

// 停止
void MainWindow::on_btnStop_clicked()
{
    player->stop();
}

// 静音按钮
void MainWindow::on_btnSound_clicked()
{
    bool mute = player->isMuted();
    player->setMuted(!mute);
    if (mute) {
        ui->btnSound->setIcon(QIcon(":/images/images/volumn.bmp"));
    } else {
        ui->btnSound->setIcon(QIcon(":/images/images/mute.bmp"));
    }
}

// 调节音量
void MainWindow::on_sliderVolumn_valueChanged(int value)
{
    player->setVolume(value);
}

// 全屏按钮
void MainWindow::on_pushButton_clicked()
{
//    ui->videoWidget->setFullScreen(true);
}

// 播放位置
void MainWindow::on_sliderPosition_valueChanged(int value)
{
    player->setPosition(value);
}
