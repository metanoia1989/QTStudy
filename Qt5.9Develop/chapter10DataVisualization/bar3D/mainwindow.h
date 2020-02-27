#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDataVisualization>

using namespace QtDataVisualization;

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

    void on_comboCamera_currentIndexChanged(int index);

    void on_sliderH_valueChanged(int value);

    void on_sliderZoom_valueChanged(int value);

    void on_sliderV_valueChanged(int value);

    void on_cBoxTheme_currentIndexChanged(int index);

    void on_cBoxBarStyle_currentIndexChanged(int index);

    void on_cBoxSelectionMode_currentIndexChanged(int index);

    void on_spinFontSize_valueChanged(int arg1);

    void on_btnBarColor_clicked();

    void on_chkBoxBackground_clicked(bool checked);

    void on_chkBoxGrid_clicked(bool checked);

    void on_chkBoxSmooth_clicked(bool checked);

    void on_chkBoxReflection_clicked(bool checked);

    void on_chkBoxReverse_clicked(bool checked);

    void on_chkBoxItemLabel_clicked(bool checked);

    void on_chkBoxAxisTitle_clicked(bool checked);

    void on_chkBoxAxisBackground_clicked(bool checked);

private:
    void iniGraph3D(); // 创建图

    Ui::MainWindow *ui;
    QWidget *graphContainer; // 图表的容器
    Q3DBars *graph3D; // 图表
    QBar3DSeries *series; // 序列
};
#endif // MAINWINDOW_H
