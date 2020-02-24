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

private slots:
    void on_comboSysStyle_currentIndexChanged(const QString &arg1);

    void on_btnNormal_clicked();

    void on_btnStyleSheet_clicked();

    void on_btnFontLarge_clicked();

    void on_btnFontSmall_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
