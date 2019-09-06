#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QSpinBox>
#include <QFontComboBox>

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
    Ui::MainWindow *ui;
    QLabel *fLabCurFile; // 状态栏里显示当前文件的Label
    QProgressBar *progressBar1; // 状态栏上的进度条
    QSpinBox *spinFontSize; // 字体大小 spinBox
    QFontComboBox *comboFont; // 字体名称 comboBox
    void initUI(); // 代码实现UI初始化

private slots:
    void on_actFontBold_triggred(bool checked);
    void on_actFontItalic_triggred(bool checked);
    void on_actFontUnder_triggred(bool checked);
    void on_txtEdit_copyAvailable(bool b);
    void on_txtEdit_selectionChanged();
};

#endif // MAINWINDOW_H
