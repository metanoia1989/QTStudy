#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTableWidgetItem>
#include "qwintspindelegate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // 为某一行创建 items
    void createItemsARow(int rowNo, QString Name, QString Sex, QDate brith,
                         QString Nation, bool isPM, int score);

    // 自定义单元格Type的类型，在创建单元格的Item时使用
    enum CellType{ctName=1000, ctSex, ctBirth, ctNation, ctPartyM, ctScore}; // 各单元格的类型
    // 各字段在表格中的列号
    enum FieldColNum{colName=0, colSex, colBirth, colNation, colScore, colPartyM};

    QLabel* labCellIndex;	// 状态栏上用于显示单元格的行号、列号
    QLabel* labCellType;	// 状态栏上用于显示单元格的type
    QLabel* lablStudID;		// 状态栏上用于显示单元格的data

    QWIntSpinDelegate spinDelegate;	// 代理组件

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
