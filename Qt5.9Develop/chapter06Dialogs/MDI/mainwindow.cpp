#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qformdoc.h"

#include <QPainter>
#include <QFileDialog>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->mdiArea);
    this->setWindowState(Qt::WindowMaximized); // 窗口最大化显示
    ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // 关闭所有子窗口
    ui->mdiArea->closeAllSubWindows();
    event->accept();
}

// 新建文件
void MainWindow::on_actDoc_New_triggered()
{

    QFormDoc *formDoc = new QFormDoc(this); // 指定父窗口
    ui->mdiArea->addSubWindow(formDoc);
    formDoc->show();

    ui->actCut->setEnabled(true);
    ui->actCopy->setEnabled(true);
    ui->actPaste->setEnabled(true);
    ui->actFont->setEnabled(true);
}

// 打开文件
void MainWindow::on_actDoc_Open_triggered()
{
    // 必须先获取当前MDI子窗口，再使用打开文件对话框，否则无法获得活动的子窗口
    bool needNew = false; // 是否需要新建子窗口
    QFormDoc *formDoc;
    if (ui->mdiArea->subWindowList().count() > 0) {
        formDoc = static_cast<QFormDoc*>(ui->mdiArea->activeSubWindow()->widget());
        needNew = formDoc->isFileOpened(); // 当前窗口已经打开文件，需要新建窗口
    } else {
        needNew = true;
    }

    QString curPath=QDir::currentPath();
    QString aFileName=QFileDialog::getOpenFileName(this,tr("打开一个文件"),curPath,
                 "C程序文件(*.h *cpp);;文本文件(*.txt);;所有文件(*.*)");
    if (aFileName.isEmpty())
        return; //如果未选择文件，退出

    if (needNew) {
        formDoc = new QFormDoc(this); // 指定父窗口
        ui->mdiArea->addSubWindow(formDoc);
    }

    formDoc->loadFromFile(aFileName); // 打开文件
    formDoc->show();

    ui->actCut->setEnabled(true);
    ui->actCopy->setEnabled(true);
    ui->actPaste->setEnabled(true);
    ui->actFont->setEnabled(true);
}

// 设置字体
void MainWindow::on_actFont_triggered()
{
    QFormDoc *formDoc = static_cast<QFormDoc*>(ui->mdiArea->activeSubWindow()->widget());
    formDoc->setEditFont();
}

void MainWindow::on_actCut_triggered()
{
    QFormDoc *formDoc = static_cast<QFormDoc*>(ui->mdiArea->activeSubWindow()->widget());
    formDoc->textCut();
}

void MainWindow::on_actCopy_triggered()
{
    QFormDoc *formDoc = static_cast<QFormDoc*>(ui->mdiArea->activeSubWindow()->widget());
    formDoc->textCopy();
}

void MainWindow::on_actPaste_triggered()
{
    QFormDoc *formDoc = static_cast<QFormDoc*>(ui->mdiArea->activeSubWindow()->widget());
    formDoc->textPaste();
}

// MDI显示模式切换
void MainWindow::on_actViewMode_triggered(bool checked)
{
    if (checked) { 	// Tab多页显示模式
        ui->mdiArea->setViewMode(QMdiArea::TabbedView);
        ui->mdiArea->setTabsClosable(true);	// 页面可关闭
        ui->actCascade->setEnabled(false);
        ui->actTile->setEnabled(false);
    } else {	// 子窗口模式
        ui->mdiArea->setViewMode(QMdiArea::SubWindowView);
        ui->actCascade->setEnabled(true);
        ui->actTile->setEnabled(true);
    }
}

// 窗口级联展开
void MainWindow::on_actCascade_triggered()
{
    ui->mdiArea->cascadeSubWindows();
}

// 平铺展开
void MainWindow::on_actTile_triggered()
{
    ui->mdiArea->tileSubWindows();
}

// 关闭全部子窗口
void MainWindow::on_actCloseAll_triggered()
{
    ui->mdiArea->closeAllSubWindows();
}

// 当前活动子窗口切换时
void MainWindow::on_mdiArea_subWindowActivated(QMdiSubWindow *arg1)
{
    Q_UNUSED(arg1);

    if (ui->mdiArea->subWindowList().count() == 0) {
        // 若子窗口个数为零
        ui->actCut->setEnabled(false);
        ui->actCopy->setEnabled(false);
        ui->actPaste->setEnabled(false);
        ui->actFont->setEnabled(false);
        ui->statusBar->setEnabled(false);
    } else {
        QFormDoc *formDoc = static_cast<QFormDoc*>(ui->mdiArea->activeSubWindow()->widget());
        ui->statusBar->showMessage(formDoc->currentFileName());	// 显示主窗口的文件名
    }
}
