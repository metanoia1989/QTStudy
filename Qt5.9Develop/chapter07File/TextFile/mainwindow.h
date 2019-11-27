#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_actOpen_IODevice_triggered();

    void on_actSave_IODevice_triggered();

    void on_actOpen_TextStream_triggered();

    void on_actSave_TextStream_triggered();

private:
    bool openTextByIODevice(const QString &aFileName);
    bool saveTextByIODevice(const QString &aFileName);
    bool openTextByStream(const QString &aFileName);
    bool saveTextByStream(const QString &aFileName);

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
