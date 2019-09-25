#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QAxObject>	// 访问Office对象类

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
    void on_writeExcelPushButton_clicked();	// 写Excel按钮单击事件槽
    void on_readExcelPushButton_clicked();	// 读Excel按钮单击事件槽
    void on_writeWordPushButton_clicked();	// 写Word按钮单击事件槽
    void on_readWordPushButton_clicked();	// 读Word按钮单击事件槽

private:
    Ui::MainWindow *ui;
    QAxObject *myexcel;		// Excel 应用程序指针
    QAxObject *myworks;		// 工作簿集指针
    QAxObject *workbook;	// 工作簿指针
    QAxObject *mysheets;	// 电子表格集指针

    QAxObject *myword;	// Word应用程序指针
    QAxObject *mydocs;	// 文档集指针
    QAxObject *document;	// 文档指针
    QAxObject *paragraph;	// 文本段指针
};

#endif // MAINWINDOW_H
