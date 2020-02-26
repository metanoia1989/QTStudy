#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->tableView);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setAlternatingRowColors(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{//更新actPost和actCancel 的状态
    Q_UNUSED(current);
    Q_UNUSED(previous);
    ui->actSubmit->setEnabled(tabModel->isDirty()); //有未保存修改时可用
    ui->actRevert->setEnabled(tabModel->isDirty());
}

// 打开数据表
void MainWindow::openTable()
{
    tabModel = new QSqlRelationalTableModel(this, DB);
    tabModel->setTable("studInfo"); // 设置数据表
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit); // OnManualSubmit, OnRowChange
    tabModel->setSort(0, Qt::AscendingOrder);

    tabModel->setHeaderData(0, Qt::Horizontal, "学号");
    tabModel->setHeaderData(1, Qt::Horizontal, "姓名");
    tabModel->setHeaderData(2, Qt::Horizontal, "性别");
    tabModel->setHeaderData(3, Qt::Horizontal, "学院");
    tabModel->setHeaderData(4, Qt::Horizontal, "专业");

    // 设置代码字段的查询关系数据表
    tabModel->setRelation(3, QSqlRelation("departments", "departID", "department")); // 学院
    tabModel->setRelation(4, QSqlRelation("majors", "majorID", "major")); // 专业

    theSelection = new QItemSelectionModel(tabModel);
    connect(theSelection, &QItemSelectionModel::currentChanged, this,
            &MainWindow::on_currentChanged);

    ui->tableView->setModel(tabModel);
    ui->tableView->setSelectionModel(theSelection);
    // 为关系型字段设置缺省代理组件
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    tabModel->select(); // 打开数据表

    ui->actOpenDb->setEnabled(false);
    ui->actRecAppend->setEnabled(true);
    ui->actRecInsert->setEnabled(true);
    ui->actRecDelete->setEnabled(true);
    ui->actFields->setEnabled(true);
}

// 打开数据库
void MainWindow::on_actOpenDb_triggered()
{
    QString aFile=QFileDialog::getOpenFileName(this,"选择数据库文件","",
                                                 "SQL Lite数据库(*.db *.db3)");
    if (aFile.isEmpty())
        return;

    //打开数据库
    DB=QSqlDatabase::addDatabase("QSQLITE"); //添加 SQL LITE数据库驱动
    DB.setDatabaseName(aFile); //设置数据库名称
    //    DB.setHostName();
    //    DB.setUserName();
    //    DB.setPassword();
    if (!DB.open())   //打开数据库
    {
        QMessageBox::warning(this, "错误", "打开数据库失败",
                             QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }

    //打开数据表
    openTable();
}

// 添加记录
void MainWindow::on_actRecAppend_triggered()
{
    tabModel->insertRow(tabModel->rowCount(),QModelIndex()); //在末尾添加一个记录
    QModelIndex curIndex=tabModel->index(tabModel->rowCount()-1,1);//创建最后一行的ModelIndex
    theSelection->clearSelection();//清空选择项
    theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);//设置刚插入的行为当前选择
}

// 插入记录
void MainWindow::on_actRecInsert_triggered()
{
    QModelIndex curIndex=ui->tableView->currentIndex();
    tabModel->insertRow(curIndex.row(),QModelIndex());

    theSelection->clearSelection();//清除已有选择
    theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);
}

// 取消修改
void MainWindow::on_actRevert_triggered()
{
    tabModel->revertAll();
    ui->actSubmit->setEnabled(false);
    ui->actRevert->setEnabled(false);
}

// 保存修改
void MainWindow::on_actSubmit_triggered()
{
    bool res=tabModel->submitAll();
    if (!res)
        QMessageBox::information(this, "消息", "数据保存错误,错误信息\n"+tabModel->lastError().text(),
                                 QMessageBox::Ok,QMessageBox::NoButton);
    else
    {
        ui->actSubmit->setEnabled(false);
        ui->actRevert->setEnabled(false);
    }
}

// 删除当前记录
void MainWindow::on_actRecDelete_triggered()
{
    tabModel->removeRow(theSelection->currentIndex().row());
    tabModel->submitAll(); //立即更
}

// 获取字段列表
void MainWindow::on_actFields_triggered()
{
    QSqlRecord  emptyRec=tabModel->record();//获取空记录，只有字段名
    QString  str;
    for (int i=0;i<emptyRec.count();i++)
        str=str+emptyRec.fieldName(i)+'\n';

    QMessageBox::information(this, "所有字段名", str,
                             QMessageBox::Ok,QMessageBox::NoButton);
}
