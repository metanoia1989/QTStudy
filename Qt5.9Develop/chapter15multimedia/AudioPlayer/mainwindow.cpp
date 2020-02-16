#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    playlist->setPlaybackMode(QMediaPlaylist::Loop); // 循环模式
    player->setPlaylist(playlist);

    // 播放器状态变化时发射
    connect(player, &QMediaPlayer::stateChanged,
            this, &MainWindow::onStateChanged);
    // 当前文件播放位置变化时发射
    connect(player, &QMediaPlayer::positionChanged,
            this, &MainWindow::onPositionChanged);
    // 文件时长变化时发射
    connect(player, &QMediaPlayer::durationChanged,
            this, &MainWindow::onDurationChanged);
    // 播放列表的当前文件变化时发射
    connect(playlist, &QMediaPlaylist::currentIndexChanged,
            this, &MainWindow::onPlaylistChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 播放器状态变化，更新按钮状态
void MainWindow::onStateChanged(QMediaPlayer::State state)
{
    ui->btnPlay->setEnabled(!(state == QMediaPlayer::PlayingState));
    ui->btnPause->setEnabled(state == QMediaPlayer::PlayingState);
    ui->btnStop->setEnabled(state == QMediaPlayer::PlayingState);
}

// 播放列表变化，更新当前播放文件名显示
void MainWindow::onPlaylistChanged(int position)
{
    ui->listWidget->setCurrentRow(position);
    QListWidgetItem *item = ui->listWidget->currentItem();
    if (item) {
        ui->LabCurMedia->setText(item->text());
    }
}

// 文件时长变化，更新进度显示
void MainWindow::onDurationChanged(qint64 duration)
{
    ui->sliderPosition->setMaximum(duration);
    int secs = duration / 1000; // 秒
    int mins = secs / 60; // 分钟
    secs = secs % 60; // 余数秒
    durationTime = QString::asprintf("%d:%d", mins, secs);
    ui->LabRatio->setText(positionTime + "/" + durationTime);
}

// 当前文件播放位置变化，更新进度显示
void MainWindow::onPositionChanged(qint64 position)
{
    if (ui->sliderPosition->isSliderDown()) {
        return;
    }
    ui->sliderPosition->setSliderPosition(position);
    int secs = position / 1000; // 秒
    int mins = secs / 60; // 分钟
    secs = secs % 60; // 余数秒
    positionTime = QString::asprintf("%d:%d", mins, secs);
    ui->LabRatio->setText(positionTime + "/" + durationTime);
}

// 添加音频文件
void MainWindow::on_btnAdd_clicked()
{
    QString curPaht = QDir::homePath(); // 获取系统当前目录
    QString dlgTitle = "选择音频文件"; // 对话框标题
    QString filter = "音频文件(*.mp3 *.wav *.wma);;mp3文件(*.mp3);;wma文件(.wma);;所有文件(*.*)";
    QStringList fileList = QFileDialog::getOpenFileNames(this, dlgTitle, curPaht, filter);

    if (fileList.count() < 1) return;

    for (int i=0; i<fileList.count(); i++) {
        QString aFile = fileList.at(i);
        playlist->addMedia(QUrl::fromLocalFile(aFile)); // 添加文件

        QFileInfo fileInfo(aFile);
        ui->listWidget->addItem(fileInfo.fileName()); // 添加到界面文件列表
    }
    if (player->state() != QMediaPlayer::PlayingState) {
        playlist->setCurrentIndex(0);
    }
    player->play();
}

// 移除一个音频文件
void MainWindow::on_btnRemove_clicked()
{
    int pos = ui->listWidget->currentRow();
    QListWidgetItem *item = ui->listWidget->takeItem(pos);
    delete item;	// 从listWidget里删除

    if (playlist->currentIndex() == pos) { // 是当前播放的曲目
        int nextPos = 0;
        if (pos >= 1) {
            nextPos = pos - 1;
        }
        playlist->removeMedia(pos);	// 从播放列表里移除
        if (ui->listWidget->count() > 0) {
            playlist->setCurrentIndex(nextPos);
            onPlaylistChanged(nextPos);
        } else {
            player->stop();
            ui->LabCurMedia->setText("无曲目");
        }
    } else {
        playlist->removeMedia(pos);
    }
}

// 清空播放列表
void MainWindow::on_btnClear_clicked()
{
    playlist->clear();
    ui->listWidget->clear();
    player->stop();
}

// 双击时切换播放文件
void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    int rowNo = index.row();
    playlist->setCurrentIndex(rowNo);
    player->play();
}

// 播放音频文件
void MainWindow::on_btnPlay_clicked()
{
    if (playlist->currentIndex() < 0) {
        playlist->setCurrentIndex(0);
    }
    player->play();
}

// 暂停播放
void MainWindow::on_btnPause_clicked()
{
    player->pause();
}

// 停止播放
void MainWindow::on_btnStop_clicked()
{
    player->stop();
}

// 前一个文件
void MainWindow::on_btnPrevious_clicked()
{
    playlist->previous();
}

// 后一个文件
void MainWindow::on_btnNext_clicked()
{
    playlist->next();
}

// 静音控制
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

// 调整音量
void MainWindow::on_sliderVolumn_valueChanged(int value)
{
    player->setVolume(value);
}

// 文件进度调控
void MainWindow::on_sliderPosition_valueChanged(int value)
{
    player->setPosition(value);
}
