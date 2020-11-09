#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void readSettings();
    void showError(QString msg);
    void loadStudentData();

private:
    Ui::MainWindow *ui;

    QString server_url; // 服务器地址
    QString keyword; // 搜索关键词
    int curr_page; // 当前页数
    int per_page; // 每页数量
};
#endif // MAINWINDOW_H
