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

    // 设置 actTab_Locate 的 enabled 属性
    void setActLocateEnable(bool enable);
    // 设置一个单元格的内容，由dlgLocate调用
    void setACellText(int row, int column, QString text);
    // 将dlgLocate指针设置为nullptr
    void setDlgLocateNull();

    void closeEvent(QCloseEvent *event);


private slots:
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);

    void on_actTab_SetSize_triggered();

    void on_actTab_SetHeader_triggered();

    void on_actTab_Locate_triggered();

    void on_tableView_clicked(const QModelIndex &index);

private:
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
