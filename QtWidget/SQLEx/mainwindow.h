#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QTableView>
#include <QListWidget>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QGroupBox *createCarGroupBox();
    QGroupBox *createFactoryGroupBox();
    QGroupBox *createDetailsGroupBox();
    void createMenuBar();
    QTableView *carView;	// 显示汽车的视图
    QTableView *factoryView;	// 显示汽车制造商的视图
    QListWidget *attribList;	// 显示车型的详细信息列表
    /* 声明相关的信息标签 */
    QLabel *profileLabel;
    QLabel *titleLabel;
};

#endif // MAINWINDOW_H
