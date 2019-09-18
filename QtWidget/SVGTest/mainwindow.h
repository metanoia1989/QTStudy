#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "svgwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createMenu();

public slots:
    void slotOpenFile();

private:
    SvgWindow *svgWindow;
};

#endif // MAINWINDOW_H
