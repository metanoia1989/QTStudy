#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QModelIndex>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 自定义槽函数
    void onStateChanged(QMediaPlayer::State state);
    void onPlaylistChanged(int position);
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);

    // ui设计器生成的槽函数

    void on_btnAdd_clicked();

    void on_btnRemove_clicked();

    void on_btnClear_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_btnPlay_clicked();

    void on_btnPause_clicked();

    void on_btnStop_clicked();

    void on_btnPrevious_clicked();

    void on_btnNext_clicked();

    void on_btnSound_clicked();

    void on_sliderVolumn_valueChanged(int value);

    void on_sliderPosition_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player; // 播放器
    QMediaPlaylist *playlist; // 播放列表
    QString durationTime;	// 总长度
    QString positionTime; 	// 当前播放位置
};
#endif // MAINWINDOW_H
