#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>

namespace Ui {
class MainWindow;
}

// 文件固定6列
const int FixedColumnCount = 6;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 当前选择的单元格发生变化时，更新状态栏的信息显示
    // 与项选择模型theSelection的currentChanged()信号关联
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);

    void on_actOpen_triggered();

    void on_actSave_triggered();

    void on_actAppend_triggered();

    void on_actInsert_triggered();

    void on_actDelete_triggered();

    void on_actModelData_triggered();

    void on_actAlignLeft_triggered();

    void on_actAlignCenter_triggered();

    void on_actAlignRight_triggered();

    void on_actFontBold_triggered(bool checked);

private:
    //打开一个文件时，从StringList初始化数据模型
    void iniModelFromStringList(QStringList&);

    // 用于状态栏的信息显示
    QLabel *LabCurFile;	// 当前文件
    QLabel *LabCellPos; // 当前单元格行列号
    QLabel *LabCellText;	// 当前单元格内容

    QStandardItemModel *theModel;	// 数据模型
    QItemSelectionModel *theSelection;	// Item选择模型

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
