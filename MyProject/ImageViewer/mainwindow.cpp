#include "mainwindow.h"
#include "utils.hpp"
#include "constants.hpp"
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QPushButton>
#include <QAction>
#include <QMenu>
#include <QLabel>
#include <QToolBar>
#include <QToolButton>
#include <QDebug>
#include <QWheelEvent>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QVBoxLayout *vlayout = new QVBoxLayout();
    QWidget *widget = new QWidget();
    widget->setLayout(vlayout);
    setCentralWidget(widget);

    imageLabel = new QLabel();
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setFixedSize(constants::ViewWidth, constants::ViewHeight);
    vlayout->addWidget(imageLabel);

    QWidget *thumbnailView = new QWidget();
    thumbnailLayout = new QHBoxLayout();
    thumbnailView->setLayout(thumbnailLayout);
    initThumbnailView();

    scrollView = new QScrollArea();
    scrollView->setFrameShape(QFrame::NoFrame); // 隐藏边框
    scrollView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    scrollView->setWidget(thumbnailView);
    scrollView->viewport()->installEventFilter(this);
    vlayout->addWidget(scrollView);

    createMainMenu();
    createToolBar();

    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    setWindowState(Qt::WindowMinimized);
//    event->ignore();
}

/**
 * @brief MainWindow::eventFilter
 * @details 监听底部thumbnail ScrollArea的鼠标滚动事件，水平移动内容
 */
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == scrollView->viewport() && event->type() == QEvent::Wheel) {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
        QCoreApplication::sendEvent(scrollView->horizontalScrollBar(), wheelEvent);
        return true;
    }

    return QObject::eventFilter(obj, event);
}

void MainWindow::initThumbnailView()
{
    if (QCoreApplication::arguments().size() > 1) {
        const QString FILENAME = QCoreApplication::arguments().at(1);
        // FILENAME now contains path and name of the file to open.
        QDir curFile{FILENAME};
        curPath = curFile.homePath();
    }
    QString file = "D:/Image/lady/pic_033.jpg";
    if (QFile::exists(file)) {
        QFileInfo curFile{file};
        curPath = curFile.absoluteDir();
    }

//    if (curPath.isNull()) {
//        imgPaths = {
//            QCoreApplication::applicationDirPath() + "/default.jpg",
//        };
//        imgIndex = 0;
//        curImage = QImage(imgPaths.at(imgIndex)).scaledToHeight(constants::ViewHeight);
//        imageLabel->setPixmap(QPixmap::fromImage(curImage));
//        return;
//    }

//    imgPaths = {
//        ":/assets/images/pic_048.jpg",
//        ":/assets/images/pic_049.jpg",
//        ":/assets/images/pic_050.jpg",
//        ":/assets/images/pic_057.jpg",
//        ":/assets/images/pic_051.jpg",
//        ":/assets/images/pic_052.jpg",
//        ":/assets/images/pic_054.jpg",
//        ":/assets/images/pic_058.jpg",
//        ":/assets/images/pic_059.jpg"
//    };
//    for (int i = 0; i < 30; i++) {
//        QLabel *label = new QLabel(QString("Image %1").arg(i));
//        QPixmap img(imgPaths.at(i % imgPaths.size()));
//        label->setPixmap(img.scaledToHeight(constants::ThumbHeight));
//        thumbnailLayout->addWidget(label);
//    }
}

void MainWindow::createMainMenu()
{
    mainMenu = new QMenu(this);

    menuAct = new QAction(this);
    menuAct->setIcon(QIcon(":/assets/icons/menu.svg"));

    QMenu *fileMenu = mainMenu->addMenu(tr("File")); // 文件菜单
    openAct = fileMenu->addAction(tr("Open file"));
    openAct->setIcon(QIcon(":/assets/icons/open.svg"));
    openAct->setIconVisibleInMenu(false);
    openAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_O));
    QAction *pasteAct = fileMenu->addAction(tr("Open image data from clipboard"));
    pasteAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_V));
    QAction *openNewAct= fileMenu->addAction(tr("Open new window"));
    openNewAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_N));
    QAction *saveAct= fileMenu->addAction(tr("Save image as ..."));
    saveAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_S));
    fileMenu->addSeparator();
    QAction *editAct = fileMenu->addAction(tr("Edit image"));
    editAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_E));
    QAction *printAct = fileMenu->addAction(tr("Print"));
    printAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_P));
    fileMenu->addSeparator();
    QAction *refreshAct = fileMenu->addAction(tr("Refresh"));
    refreshAct->setShortcut(Qt::Key_F5);
    QAction *reloadAct = fileMenu->addAction(tr("Reload image"));
    reloadAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_R));
    QAction *reloadListAct = fileMenu->addAction(tr("Reload image list"));
    reloadListAct->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_R));

    QMenu *navigationMenu = mainMenu->addMenu(tr("Navigation")); // 导航菜单
    nextAct = navigationMenu->addAction(tr("View next image"));
    nextAct->setIcon(QIcon(":/assets/icons/next.svg"));
    nextAct->setIconVisibleInMenu(false);
    QList<QKeySequence> keys { Qt::Key_Right, Qt::Key_PageDown };
    nextAct->setShortcuts(keys);
    prevAct = navigationMenu->addAction(tr("View previous image"));
    prevAct->setIcon(QIcon(":/assets/icons/back.svg"));
    prevAct->setIconVisibleInMenu(false);
    keys = { Qt::Key_Left, Qt::Key_PageUp };
    prevAct->setShortcuts(keys);
    navigationMenu->addSeparator();
    QAction *goToAct = navigationMenu->addAction(tr("Go to ..."));
    goToAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_G));
    QAction *goFirst= navigationMenu->addAction(tr("Go to the first image"));
    goFirst->setShortcut(Qt::Key_Home);
    QAction *goLast = navigationMenu->addAction(tr("Go to the last image"));
    goLast->setShortcut(Qt::Key_End);

    QMenu *zoomMenu = mainMenu->addMenu(tr("Zoom")); // 缩放菜单
    zoomInAct = zoomMenu->addAction(tr("Zoom in"));
    zoomInAct->setIcon(QIcon(":/assets/icons/zoomin.svg"));
    zoomInAct->setIconVisibleInMenu(false);
    zoomInAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Equal));
    zoomOutAct = navigationMenu->addAction(tr("Zoom out"));
    zoomOutAct->setIcon(QIcon(":/assets/icons/zoomout.svg"));
    zoomOutAct->setIconVisibleInMenu(false);
    zoomOutAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Less));
    QAction *actualSizeAct = zoomMenu->addAction("Actual size");
    actualSizeAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_0));
    zoomMenu->addSeparator();
    QAction *autoZoomAct = zoomMenu->addAction("Auto zoom");
    autoZoomAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_A));
    scaleToWidthAct = zoomMenu->addAction(tr("Scale to width"));
    scaleToWidthAct->setIcon(QIcon(":/assets/icons/scaletowidth.svg"));
    scaleToWidthAct->setIconVisibleInMenu(false);
    scaleToWidthAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_W));
    scaleToHeightAct = zoomMenu->addAction(tr("Scale to height"));
    scaleToHeightAct->setIcon(QIcon(":/assets/icons/scaletoheight.svg"));
    scaleToHeightAct->setIconVisibleInMenu(false);
    scaleToHeightAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_H));
    QAction *scaleToFitAct = zoomMenu->addAction(tr("Scale to fit"));
    scaleToFitAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_division));
    QAction *scaleToFillAct = zoomMenu->addAction(tr("Scale to fill"));
    scaleToFillAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_D));
    QAction *lockZoomAct = zoomMenu->addAction(tr("Lock zoom ratio"));
    lockZoomAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_L));

    imageMenu = mainMenu->addMenu(tr("Image")); // 图片菜单，同时也是图片展示区域的右键菜单

    QMenu *viewChannelMenu = imageMenu->addMenu(tr("View channels")); // 颜色通道菜单
    QActionGroup *viewChannelGrp = new QActionGroup(viewChannelMenu);
    QAction *redChannelAct = viewChannelMenu->addAction(tr("Red"));
    QAction *greenChannelAct = viewChannelMenu->addAction(tr("Green"));
    QAction *blueChannelAct = viewChannelMenu->addAction(tr("Blue"));
    QAction *blackChannelAct = viewChannelMenu->addAction(tr("Black"));
    QAction *alphaChannelAct = viewChannelMenu->addAction(tr("Alpha"));
    QAction *allChannelAct = viewChannelMenu->addAction(tr("All"));
    redChannelAct->setCheckable(true);
    greenChannelAct->setCheckable(true);
    blueChannelAct->setCheckable(true);
    blackChannelAct->setCheckable(true);
    alphaChannelAct->setCheckable(true);
    allChannelAct->setCheckable(true);

    viewChannelGrp->setExclusive(true);
    viewChannelGrp->addAction(redChannelAct);
    viewChannelGrp->addAction(greenChannelAct);
    viewChannelGrp->addAction(blueChannelAct);
    viewChannelGrp->addAction(blackChannelAct);
    viewChannelGrp->addAction(alphaChannelAct);
    viewChannelGrp->addAction(allChannelAct);
    allChannelAct->setChecked(true);

    rotateLeftAct = imageMenu->addAction("Rotate left");
    rotateLeftAct->setIcon(QIcon(":/assets/icons/leftrotate.svg"));
    rotateLeftAct->setIconVisibleInMenu(false);
    rotateLeftAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Comma));
    rotateRightAct = imageMenu->addAction("Rotate left");
    rotateRightAct->setIcon(QIcon(":/assets/icons/rightrotate.svg"));
    rotateRightAct->setIconVisibleInMenu(false);
    rotateRightAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Period));
    filpHorizontalAct = imageMenu->addAction("Filp Horizontal");
    filpHorizontalAct->setIcon(QIcon(":/assets/icons/fliphorz.svg"));
    filpHorizontalAct->setIconVisibleInMenu(false);
    filpHorizontalAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Semicolon));
    filpVerticalAct = imageMenu->addAction("Filp Vertical");
    filpVerticalAct->setIcon(QIcon(":/assets/icons/flipvert.svg"));
    filpVerticalAct->setIconVisibleInMenu(false);
    filpVerticalAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_QuoteLeft));
    imageMenu->addSeparator();
    QAction *renameAct = imageMenu->addAction(tr("Rename image"));
    renameAct->setShortcut(Qt::Key_F2);
    deleteAct = imageMenu->addAction(tr("Move to recycle bin"));
    deleteAct->setIcon(QIcon(":/assets/icons/delete.svg"));
    deleteAct->setIconVisibleInMenu(false);
    deleteAct->setShortcut(Qt::Key_Delete);
    QAction *completeDelAct = imageMenu->addAction(tr("Delete from hard disk"));
    completeDelAct->setShortcut(QKeySequence(Qt::SHIFT+Qt::Key_Delete));
    imageMenu->addSeparator();
    QAction *setBgAct = imageMenu->addAction(tr("Set as Desktop background"));
    QAction *setLkAct = imageMenu->addAction(tr("Set as Lock screen image"));
    QAction *locationAct = imageMenu->addAction(tr("Open image location"));
    locationAct->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_L));
    imageMenu->addSeparator();
    QAction *propertiesAct = imageMenu->addAction(tr("Image properties"));
    propertiesAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_I));

    QMenu *clipboardMenu = mainMenu->addMenu(tr("Clipboard")); // 剪切板菜单
    copyAct = clipboardMenu->addAction("Copy");
    copyAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_C));
    QAction *copyDataAct = clipboardMenu->addAction("Copy image data");
    copyDataAct->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_C));
    QAction *cutAct = clipboardMenu->addAction("Cut");
    cutAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_X));
    clipboardMenu->addSeparator();
    QAction *copyPathAct = clipboardMenu->addAction("Copy image path");
    clipboardMenu->addSeparator();
    QAction *clearCbAct = clipboardMenu->addAction("Clear clipboard");
    clearCbAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_QuoteDbl));

    mainMenu->addSeparator();

    windowFitAct = mainMenu->addAction(tr("Window fit"));
    windowFitAct->setIcon(QIcon(":/assets/icons/autosizewindow.svg"));
    windowFitAct->setIconVisibleInMenu(false);
    windowFitAct->setShortcut(Qt::Key_F9);
    fullScreenAct = mainMenu->addAction(tr("Window fit"));
    fullScreenAct->setIcon(QIcon(":/assets/icons/fullscreen.svg"));
    fullScreenAct->setIconVisibleInMenu(false);
    fullScreenAct->setShortcut(QKeySequence(Qt::ALT+Qt::Key_Enter));
    fullScreenAct->setShortcut(QKeySequence(Qt::ALT+Qt::Key_Enter));

    QMenu *slideshowMenu = mainMenu->addMenu(tr("Slideshow")); // 幻灯片菜单
    QAction *startSlideshowAct = slideshowMenu->addAction(tr("Start slideshow"));
    startSlideshowAct->setShortcut(Qt::Key_F11);
    QAction *pauseSlideshowAct = slideshowMenu->addAction(tr("Pause/Resume slideshow"));
    pauseSlideshowAct->setShortcut(Qt::Key_Space);
    QAction *exitSlideshowAct = slideshowMenu->addAction(tr("Exit slideshow"));
    exitSlideshowAct->setShortcut(Qt::Key_Escape);

    mainMenu->addSeparator();

    QMenu *layoutMenu = mainMenu->addMenu(tr("Layout")); // 布局菜单
    QAction *toolbarAct = layoutMenu->addAction("Toolbar");
    toolbarAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_F1));
    toolbarAct->setCheckable(true);
    toolbarAct->setChecked(true);
    thumbnailPanelAct = layoutMenu->addAction(tr("Thumbnail panel"));
    thumbnailPanelAct->setIcon(QIcon(":/assets/icons/thumbnail.svg"));
    thumbnailPanelAct->setIconVisibleInMenu(false);
    thumbnailPanelAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_T));
    thumbnailPanelAct->setCheckable(true);
    QAction *checkerboardBgAct = layoutMenu->addAction(tr("Checkerboard background"));
    checkerboardBgAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_B));
    checkerboardBgAct->setCheckable(true);
    checkerboardBgAct->setChecked(true);
    layoutMenu->addSeparator();
    QAction *keepTopAct = layoutMenu->addAction(tr("Keep widnow always on top"));


    QMenu *toolsMenu = mainMenu->addMenu(tr("Tools")); // 工具菜单
    QAction *colorPickerAct = toolsMenu->addAction(tr("Color picker"));
    colorPickerAct->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_K));
    QAction *pageNavAct = toolsMenu->addAction(tr("Page navigation"));
    pageNavAct->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_J));

    mainMenu->addSeparator();
    QAction *settingsAct = mainMenu->addAction(tr("Settings"));
    settingsAct->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_P));

    QMenu *helpMenu = mainMenu->addMenu(tr("Help")); // 帮助菜单
    QAction *aboutAct = helpMenu->addAction(tr("About"));
    aboutAct->setShortcut(Qt::Key_F1);
    QAction *chkUpdateAct = helpMenu->addAction(tr("Check for update"));
    QAction *reportAct = helpMenu->addAction(tr("Report an issue"));
    QAction *launchConfigureAct = helpMenu->addAction(tr("First-lanuch configurations"));

    QAction *exitAct = mainMenu->addAction(tr("Exit"));
    exitAct->setShortcut(Qt::Key_Escape);
}

void MainWindow::createToolBar()
{
    QWidget *spacerLeft = new QWidget();
    spacerLeft->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QWidget *spacerRight = new QWidget();
    spacerRight->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QToolBar *toolbar = addToolBar("Main ToolBar");
    toolbar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    toolbar->setMovable(false);
    toolbar->addWidget(spacerLeft);
    toolbar->addAction(prevAct);
    toolbar->addAction(nextAct);
    toolbar->addSeparator();
    toolbar->addAction(rotateLeftAct);
    toolbar->addAction(rotateRightAct);
    toolbar->addAction(filpHorizontalAct);
    toolbar->addAction(filpVerticalAct);
    toolbar->addSeparator();
    toolbar->addAction(scaleToWidthAct);
    toolbar->addAction(scaleToHeightAct);
    toolbar->addAction(zoomInAct);
    toolbar->addAction(zoomOutAct);
    toolbar->addSeparator();
    toolbar->addAction(openAct);
    toolbar->addAction(windowFitAct);
    toolbar->addSeparator();
    toolbar->addAction(deleteAct);
    toolbar->addWidget(spacerRight);
    toolbar->addAction(menuAct);

    // 点击菜单按钮，弹出菜单
    QWidget *menuWidget = toolbar->widgetForAction(menuAct);
    connect(menuAct, &QAction::triggered, [=]{
        int x=  menuWidget->width() - mainMenu->sizeHint().width() + 2;
        mainMenu->popup(menuWidget->mapToGlobal(QPoint(x, menuWidget->height())));
    });

    toolbar->setIconSize(QSize(40, 40));
}

