#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QImage;
class QMenu;
class QScrollArea;
class QHBoxLayout;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void createMainMenu();  // 创建主菜单，包括了初始化QAction
    void createToolBar(); // 创建工具条
    void initThumbnailView(); // 初始化thumbnail列表


    QImage curImage; // 当前查看的图片
    QList<QString> imgPaths;  // 一个目录下的所有图片路径
    QList<QPixmap> thumbnails; // 所有图片的缩略图
    int index; // 选择图片的索引

    QLabel *imageLabel;
    QScrollArea *scrollView;
    QHBoxLayout *thumbnailLayout;

    QMenu *mainMenu;
    QMenu *imageMenu;
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
