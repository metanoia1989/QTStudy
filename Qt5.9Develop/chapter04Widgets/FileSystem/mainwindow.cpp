#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // QFileSystemModel 提供单独线程访问系统目录文件
    model = new QFileSystemModel(this);
    model->setRootPath(QDir::currentPath());	// 设置根目录

    ui->treeView->setModel(model);	// 设置数据模型
    ui->listView->setModel(model);
    ui->tableView->setModel(model);

    // 关联信号槽，treeView 单击时，其目录设置为 listView 和 tableView 的根节点
    // QModelIndex是当前节点的模型索引（指针）
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)),
            ui->listView, SLOT(setRootIndex(QModelIndex)));
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)),
            ui->tableView, SLOT(setRootIndex(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 单击一个节点时，下方的标签将显示节点的信息
void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
     ui->chkIsDir->setChecked(model->isDir(index));
     ui->LabPath->setText(model->filePath(index));
     ui->LabType->setText(model->type(index));

     ui->LabFileName->setText(model->fileName(index));

     int size = static_cast<int>(model->size(index) / 1024);
     if (size < 1024) {
         ui->LabFileSize->setText(QString("%1 KB").arg(size));
     } else {
         ui->LabFileSize->setText(QString::asprintf("%.1f MB", size / 1024.0));
     }
}
