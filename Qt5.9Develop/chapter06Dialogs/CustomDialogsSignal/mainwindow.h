#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include    <QLabel>
#include    <QStandardItemModel>
#include    <QItemSelectionModel>
#include    <QModelIndex>
#include "qwdialogheaders.h"
#include "qwdialoglocate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 将dlgLocate指针设置为nullptr
    void selectACell(int row, int column);	// 选择一个单元格由dlgLocate调用



private slots:
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);

    void on_actTab_SetSize_triggered();
    void on_actTab_SetHeader_triggered();
    void on_actTab_Locate_triggered();
    void on_tableView_clicked(const QModelIndex &index);

public slots:
    void setACellText(int row, int column, QString &text);	// 设置单元格内容
    void setActLocateEnable(bool enable);	// 设置actTab_Locate的enabled属性

signals:
    void cellIndexChanged(int rowNo, int colNo);	// 当前单元格发生变化

private:
    void closeEvent(QCloseEvent *event);

    // 用于状态栏的信息显示
    QLabel  *LabCellPos;    //当前单元格行列号
    QLabel  *LabCellText;   //当前单元格内容

    QStandardItemModel  *theModel;//数据模型
    QItemSelectionModel *theSelection;//Item选择模型

    QWDialogHeaders *dlgSetHeaders = nullptr; // 设置表头对话框，一次创建，exec() 重复调用
    QWDialogLocate *dlgLocate = nullptr; // 定位单元对话框，show() 调用，关闭时自己删除

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
