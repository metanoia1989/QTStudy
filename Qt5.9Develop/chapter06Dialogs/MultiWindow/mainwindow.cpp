#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qformdoc.h"
#include "qformtable.h"

#include <QPainter>
#include <QFileDialog>


// 绘制窗口背景图片
void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    int height = this->height() - ui->mainToolBar->height() - ui->statusBar->height();
    painter.drawPixmap(0, ui->mainToolBar->height(), this->width(),
                       height, QPixmap(":/images/images/back2.jpg"));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear(); // 清除所有页面
    ui->tabWidget->setTabsClosable(true); // Page 有关闭按钮，可被关闭

    this->setCentralWidget(ui->tabWidget);
    this->setWindowState(Qt::WindowMaximized);	// 窗口最大化显示
    this->setAutoFillBackground(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 嵌入式Widget，创建QFormDoc窗体，并在tabWidget中显示
void MainWindow::on_actWidgetInsite_triggered()
{
    // 指定父窗口则传入this，不指定则使用show()方法显示
    QFormDoc *formDoc = new QFormDoc(this);
    formDoc->setAttribute(Qt::WA_DeleteOnClose);

    int cur = ui->tabWidget->addTab(formDoc,
            QString::asprintf("Doc %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}

// 独立Widget窗口
void MainWindow::on_actWidget_triggered()
{
    QFormDoc *formDoc = new QFormDoc();
    formDoc->setAttribute(Qt::WA_DeleteOnClose);
    formDoc->setWindowTitle("基于QWidget的窗体，无父窗口，关闭时删除");
    formDoc->setWindowFlag(Qt::Window, true);
    formDoc->setWindowOpacity(0.9);
    formDoc->show();
}

// 嵌入式MainWindow
void MainWindow::on_actWindowInsite_triggered()
{
    QFormTable *formTable = new QFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tabWidget->addTab(formTable,
                QString::asprintf("Table %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}

// 独立MainWindow窗口
void MainWindow::on_actWindow_triggered()
{
    // 主窗口关闭时，所有QFormTable类窗口自动删除
    QFormTable *formTable = new QFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose);
    formTable->setWindowTitle("基于QMainWindow的窗口，指定父窗口，关闭时删除");
    formTable->show();
}

// 关闭Tab
void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (index < 0) {
        return;
    }
    QWidget *aForm = ui->tabWidget->widget(index);
    aForm->close();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    Q_UNUSED(index);
    bool en = ui->tabWidget->count() > 0; // 无页面时，actions 禁用
    ui->tabWidget->setVisible(en);
}
