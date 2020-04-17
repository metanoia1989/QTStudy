#include "mainwindow.h"
#include "utils.hpp"
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

    imageLabel = new QLabel("图片展示");
    imageLabel->setPixmap(QPixmap(":/assets/images/pic_054.jpg"));
    imageLabel->setAlignment(Qt::AlignCenter);
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
 * @param obj
 * @param event
 * @return
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
    imgPaths = {
        ":/assets/images/pic_048.jpg",
        ":/assets/images/pic_049.jpg",
        ":/assets/images/pic_050.jpg",
        ":/assets/images/pic_057.jpg",
        ":/assets/images/pic_051.jpg",
        ":/assets/images/pic_052.jpg",
        ":/assets/images/pic_054.jpg",
        ":/assets/images/pic_058.jpg",
        ":/assets/images/pic_059.jpg"
    };
    for (int i = 0; i < 30; i++) {
        QLabel *label = new QLabel(QString("Image %1").arg(i));
        QPixmap img(imgPaths.at(i % imgPaths.size()));
        label->setPixmap(img.scaled(113, 125, Qt::KeepAspectRatio));
        thumbnailLayout->addWidget(label);
    }
}

void MainWindow::createMainMenu()
{
    auto awesome = qtAwesome();
    mainMenu = new QMenu(this);

    menuAct = new QAction(this);
    menuAct->setIcon((awesome->icon(fa::bars)));

    QMenu *fileMenu = mainMenu->addMenu(tr("File")); // 文件菜单
    openAct = fileMenu->addAction(tr("Open file"));
    openAct->setIcon(awesome->icon(fa::folderopen));
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
    nextAct->setIcon(awesome->icon(fa::arrowright));
    nextAct->setIconVisibleInMenu(false);
    QList<QKeySequence> keys { Qt::Key_Right, Qt::Key_PageDown };
    nextAct->setShortcuts(keys);
    prevAct = navigationMenu->addAction(tr("View previous image"));
    prevAct->setIcon(awesome->icon(fa::arrowleft));
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
    zoomInAct->setIcon(awesome->icon(fa::searchplus));
    zoomInAct->setIconVisibleInMenu(false);
    zoomInAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Equal));
    zoomOutAct = navigationMenu->addAction(tr("Zoom out"));
    zoomOutAct->setIcon(awesome->icon(fa::searchminus));
    zoomOutAct->setIconVisibleInMenu(false);
    zoomOutAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Less));
    QAction *actualSizeAct = zoomMenu->addAction("Actual size");
    actualSizeAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_0));
    zoomMenu->addSeparator();
    QAction *autoZoomAct = zoomMenu->addAction("Auto zoom");
    autoZoomAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_A));
    scaleToWidthAct = zoomMenu->addAction(tr("Scale to width"));
    scaleToWidthAct->setIcon(awesome->icon(fa::textwidth));
    scaleToWidthAct->setIconVisibleInMenu(false);
    scaleToWidthAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_W));
    scaleToHeightAct = zoomMenu->addAction(tr("Scale to height"));
    scaleToHeightAct->setIcon(awesome->icon(fa::textheight));
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
    rotateLeftAct->setIcon(awesome->icon(fa::undo));
    rotateLeftAct->setIconVisibleInMenu(false);
    rotateLeftAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Comma));
    rotateRightAct = imageMenu->addAction("Rotate left");
    rotateRightAct->setIcon(awesome->icon(fa::retweet));
    rotateRightAct->setIconVisibleInMenu(false);
    rotateRightAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Period));
    filpHorizontalAct = imageMenu->addAction("Filp Horizontal");
    filpHorizontalAct->setIcon(awesome->icon(fa::expand));
    filpHorizontalAct->setIconVisibleInMenu(false);
    filpHorizontalAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Semicolon));
    filpVerticalAct = imageMenu->addAction("Filp Vertical");
    filpVerticalAct->setIcon(awesome->icon(fa::compress));
    filpVerticalAct->setIconVisibleInMenu(false);
    filpVerticalAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_QuoteLeft));
    imageMenu->addSeparator();
    QAction *renameAct = imageMenu->addAction(tr("Rename image"));
    renameAct->setShortcut(Qt::Key_F2);
    deleteAct = imageMenu->addAction(tr("Move to recycle bin"));
    deleteAct->setIcon(awesome->icon(fa::trash));
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
    copyAct->setIcon(awesome->icon(fa::copy));
    copyAct->setIconVisibleInMenu(false);
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
    windowFitAct->setIcon(awesome->icon(fa::windows));
    windowFitAct->setIconVisibleInMenu(false);
    windowFitAct->setShortcut(Qt::Key_F9);
    framelessAct = mainMenu->addAction(tr("Frameless"));
    framelessAct->setIcon(awesome->icon(fa::genderless));
    framelessAct->setIconVisibleInMenu(false);
    framelessAct->setShortcut(Qt::Key_F10);
    QAction *fullScreenAct = mainMenu->addAction(tr("Full screen"));
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
    thumbnailPanelAct->setIcon(awesome->icon(fa::image));
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
    toolbar->addAction(framelessAct);
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

