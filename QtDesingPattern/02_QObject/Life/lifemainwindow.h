#ifndef LIFEMAINWINDOW_H
#define LIFEMAINWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class LifeMainWindow; }
QT_END_NAMESPACE

class LifeWidget;

class LifeMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LifeMainWindow(QWidget *parent = nullptr);
    ~LifeMainWindow();
    void closeEvent(QCloseEvent *event) override;
    static int neighborCount(const QImage& img, int x, int y);

    enum { DEAD=0, ALIVE = 1 };

private slots:
    void on_actionAbout_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionQuit_triggered();
    void on_actionClear_triggered();
    void on_actionStartStop_triggered(bool checked);
    void on_actionPopulate_Randomly_triggered();
    void calculate();

private:
    Ui::LifeMainWindow *ui;
    QSize m_boardSize;
    LifeWidget *m_lifeWidget;
    QImage m_current;
    int m_numGenerations;
    QElapsedTimer m_timer;
    bool m_running;
};
#endif // LIFEMAINWINDOW_H
