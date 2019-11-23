#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

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
    void on_actListIni_triggered();

    void on_actListInsert_triggered();

    void on_actListAppend_triggered();

    void on_actListDelete_triggered();

    void on_actListClear_triggered();

    void on_actSelAll_triggered();

    void on_actSelNone_triggered();

    void on_actSelInvs_triggered();

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

    void on_chkBoxListEditable_clicked(bool checked);

private:
    void setActionsForButton();
    void createSelectionPopMenu();

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
