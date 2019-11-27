#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>

#include "qwintspindelegate.h"
#include "qwfloatspindelegate.h"
#include "qwcomboboxdelegate.h"

namespace Ui {
class MainWindow;
}

const int FixedColumnCount = 6; // 文件固定6行

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
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

    void on_actTabReset_triggered();

    void on_actOpenBin_triggered();

    void on_actSaveBin_triggered();

private:
    void resetTable(int aRowCount);	// 表格复位，设定行数
    bool saveDataAsStream(QString& aFileName);	// 将数据保存为数据流文件
    bool openDataAsStream(QString& aFileName);	// 读取数据流文件
    bool saveBinaryFile(QString& aFileName);	// 保存为二进制文件
    bool openBinaryFile(QString& aFileName);	// 打开为二进制文件

    // 用于状态栏的信息显示
    QLabel *LabCellPos;	// 当前单元格行号
    QLabel *LabCellText;	// 当前单元格内容

    QWIntSpinDelegate intSpinDelegate;	// 整型数
    QWFloatSpinDelegate floatSpinDelegate;	// 浮点数
    QWComboBoxDelegate comboBoxDelegate;	// 列表选择

    QStandardItemModel *theModel;	// 数据模型
    QItemSelectionModel *theSelection;	// Item选择模型

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
