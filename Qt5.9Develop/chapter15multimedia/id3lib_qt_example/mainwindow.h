#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCore>
#include <QtWidgets>

// Add this to statically link ID3 to your project
// Make it 3 to link dynamically
#define ID3LIB_LINKOPTION 3

#include "id3.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openBtn_pressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
