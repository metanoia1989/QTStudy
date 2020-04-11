#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QImage;
class QMenu;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createMainMenu();  // 创建主菜单，包括了初始化QAction
    void createToolBar(); // 创建工具条


    QImage image;
    QLabel *imageLabel;

    QMenu *mainMenu;
    QAction *menuAct;
    QAction *prevAct;
    QAction *nextAct;
    QAction *rotateLeftAct;
    QAction *rotateRightAct;
    QAction *filpHorizontalAct;
    QAction *filpVerticalAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *scaleToHeightAct;
    QAction *scaleToWidthAct;
    QAction *normalSizeAct;
    QAction *windowFitAct;
    QAction *fullScreenAct;
    QAction *openAct;
    QAction *copyAct;
    QAction *deleteAct;
    QAction *thumbnailPanelAct;

    QAction *framelessAct;
    QAction *settingsAct;
    QAction *exitAct;
};
#endif // MAINWINDOW_H
