#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QLabel>

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
    void on_actAddFolder_triggered();

    void on_actZoomFitH_triggered();

    void on_actZoomFitW_triggered();

    void on_actZoomIn_triggered();

    void on_actZoomOut_triggered();

    void on_actZoomRealSize_triggered();

    void on_actAddFiles_triggered();

    void on_actDeleteItem_triggered();

    void on_actScanItems_triggered();

    void on_treeFiles_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);


    void on_actDockVisible_toggled(bool arg1);

    void on_actDockFloat_triggered(bool checked);

    void on_dockWidget_visibilityChanged(bool visible);

    void on_dockWidget_topLevelChanged(bool topLevel);

private:
    // 目录树的初始化
    void iniTree();
    // 添加一个目录节点
    void addFloderItem(QTreeWidgetItem *parItem, QString dirName);
    // 从目录全名称中获取最后的文件夹名
    QString getFinalFolderName(const QString &fullPathName);
    // 添加一个图片节点
    void addImageItem(QTreeWidgetItem *parItem, QString aFilename);
    // 显示一个图片节点的图片
    void displayImage(QTreeWidgetItem *item);
    // 遍历改变节点标题
    void changeItemCaption(QTreeWidgetItem *item);


    // 枚举类型 treeItemType，用于创建 QTreeWidgetItem 时作为节点的 type，自定义类型必须大于 1000
    // itTopItem 顶层节点；itGroupItem 组节点；itImageItem 图片
    enum treeItemType{ itTopItem = 1001, itGroupItem, itImageItem };
    // 枚举类型，表示列号
    enum treeColNum{ colItem = 0, colItemType = 1 }; // 目录树列的编号定义

    QLabel *LabFileName;	// 状态栏显示的文件名
    QPixmap curPixmap; // 当前的图片
    double pixRatio;	// 当前图片缩放比例

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
