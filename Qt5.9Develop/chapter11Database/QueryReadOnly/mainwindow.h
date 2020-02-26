#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QString>
#include <QtSql>
#include <QDataWidgetMapper>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // QTableView的SelectionModel的行发生了变化，进行处理
    void on_currentRowChanged(const QModelIndex &current, const QModelIndex &previous);

    void on_actOpenDB_triggered();

    void on_actRecFirst_triggered();

    void on_actRecPrevious_triggered();

    void on_actRecNext_triggered();

    void on_actRecLast_triggered();

private:
    void openTable(); // 打开数据表
    void refreshTableView(); // 移动记录时刷新TableView的当前行

    Ui::MainWindow *ui;
    QLabel *LabInfo;
    QSqlDatabase DB; // 数据库
    QSqlQueryModel *qryModel; // 数据模型
    QItemSelectionModel *theSelection; // 选择模型
    QDataWidgetMapper *dataMapper; // 数据界面映射
};
#endif // MAINWINDOW_H
