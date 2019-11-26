#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actDoc_New_triggered();

    void on_actDoc_Open_triggered();

    void on_actViewMode_triggered(bool checked);

    void on_actCascade_triggered();

    void on_actTile_triggered();

    void on_actCloseAll_triggered();

    void on_actFont_triggered();

    void on_actCut_triggered();

    void on_actCopy_triggered();

    void on_actPaste_triggered();

    void on_mdiArea_subWindowActivated(QMdiSubWindow *arg1);

private:
    void closeEvent(QCloseEvent *event);

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
