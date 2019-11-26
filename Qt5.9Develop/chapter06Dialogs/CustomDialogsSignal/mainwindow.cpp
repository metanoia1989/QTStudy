#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qwdialogsize.h"

#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    theModel = new QStandardItemModel(10,5,this); //创建数据模型
    theSelection = new QItemSelectionModel(theModel);//Item选择模型
    connect(theSelection,SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));

    //为tableView设置数据模型
    ui->tableView->setModel(theModel); //设置数据模型
    ui->tableView->setSelectionModel(theSelection);//设置选择模型

    setCentralWidget(ui->tableView); //

//创建状态栏组件
    LabCellPos = new QLabel("当前单元格：",this);
    LabCellPos->setMinimumWidth(180);
    LabCellPos->setAlignment(Qt::AlignHCenter);

    LabCellText = new QLabel("单元格内容：",this);
    LabCellText->setMinimumWidth(200);


    ui->statusBar->addWidget(LabCellPos);
    ui->statusBar->addWidget(LabCellText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setActLocateEnable(bool enable)
{
    ui->actTab_Locate->setEnabled(enable);
}

// 定位到单元格，并设置字符串
void MainWindow::setACellText(int row, int column, QString &text)
{
    QModelIndex index = theModel->index(row, column);
    theSelection->clearSelection(); // 清除现有选择
    // 定位到单元格
    theSelection->setCurrentIndex(index, QItemSelectionModel::Select);
    theModel->setData(index, text, Qt::DisplayRole);	// 设置单元格字符串
}

void MainWindow::selectACell(int row, int column)
{
    QModelIndex index=theModel->index(row,column);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(index,QItemSelectionModel::Select);
}

void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if (current.isValid()) //当前模型索引有效
    {
        LabCellPos->setText(QString::asprintf("当前单元格：%d行，%d列",
                                  current.row(),current.column())); //显示模型索引的行和列号
        QStandardItem   *aItem;
        aItem=theModel->itemFromIndex(current); //从模型索引获得Item
        this->LabCellText->setText("单元格内容："+aItem->text()); //显示item的文字内容
    }
}


// 窗口关闭时询问是否退出
void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton result = QMessageBox::question(this, "确认",
        "确认要退出本程序吗？", QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel|QMessageBox::No);
    if (result == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

// 设置行数列数 模态对话框，动态创建，用过后删除
void MainWindow::on_actTab_SetSize_triggered()
{
    // 创建对话框
    QWDialogSize *dlgTableSize = new QWDialogSize(this);
    Qt::WindowFlags flags = dlgTableSize->windowFlags();
    // 设置对话框固定大小
    dlgTableSize->setWindowFlags(flags|Qt::MSWindowsFixedSizeDialogHint);
    // 对话框数据初始化
    dlgTableSize->setRowColumn(theModel->rowCount(), theModel->columnCount());

    int ret = dlgTableSize->exec(); // 以模态方式显示对话框，用户关闭对话框时返回 DialogCode 值
    // 如果设置了 Qt::WA_DeleteOnClose 对话框被释放，无法获得返回值
    if (ret == QDialog::Accepted) {
        int cols = dlgTableSize->columnCount();
        theModel->setColumnCount(cols);
        int rows = dlgTableSize->rowCount();
        theModel->setRowCount(rows);
    }
    delete dlgTableSize; // 删除对话框

}

// 设置表头标题，一次创建，多次调用，对话框关闭时只隐藏
void MainWindow::on_actTab_SetHeader_triggered()
{
    // 如果对象没有被创建过，就创建对象
    if (dlgSetHeaders == nullptr) {
        // 主窗口释放时，才会自动删除此对话框对象
        dlgSetHeaders = new QWDialogHeaders(this);
    }
    // 如果表头列数变化，重新初始化
    if (dlgSetHeaders->headerList().count() != theModel->columnCount()) {
        QStringList strList;
        // 获取现有的表头标题
        for (int i = 0; i < theModel->columnCount(); i++) {
            strList.append(theModel->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
        }
        dlgSetHeaders->setHeaderList(strList);	 // 用于对话框初始化显示
    }

    int ret = dlgSetHeaders->exec(); // 以模态方式显示对话框
    if (ret == QDialog::Accepted) {
        // 获取对话框上修改后的StringList
        QStringList strList = dlgSetHeaders->headerList();
        theModel->setHorizontalHeaderLabels(strList);	// 设置模型的表头标题
    }
}

// 单元格定位，创建StayOnTop的对话框，对话框关闭时自动删除
void MainWindow::on_actTab_Locate_triggered()
{
    // 通过控制actTab_Locate的enable属性避免重复点击
//    ui->actTab_Locate->setEnabled(false);
    QWDialogLocate *dlgLocate; // 定位单元格对话框，show()调用，关闭时自己删除
    dlgLocate = new QWDialogLocate(this); // 创建对话框，传递指针
    // 对话框关闭时自动删除对话框对象，用于不需要读取返回值的对话框
    // 如果需要获取对话框的返回值，不能设置该属性，可以在调用完对话框后删除对话框
    dlgLocate->setAttribute(Qt::WA_DeleteOnClose); // 对话框关闭时自动删除对话框对象
    Qt::WindowFlags flags = dlgLocate->windowFlags(); // 获取已有flags
    // 对话框设置为固定大小和StayOnTop
    dlgLocate->setWindowFlags(flags|Qt::WindowStaysOnTopHint);
    // 对话框初始化设置
    dlgLocate->setSpinRange(theModel->rowCount(), theModel->columnCount());
    QModelIndex curIndex = theSelection->currentIndex();
    if (curIndex.isValid()) {
        dlgLocate->setSpinValue(curIndex.row(), curIndex.column());
    }
    // 对话框释放信号，设置单元格文字
    connect(dlgLocate, SIGNAL(changeCellText(int, int, QString&)),
            this, SLOT(setACellText(int, int, QString&)));
    // 对话框是否信号，设置action的属性
    connect(dlgLocate, SIGNAL(changeActionEnable(bool)),
            this, SLOT(setActLocateEnable(bool)));
    // 主窗口是否信号，修改对话框上的spinBox的值
    connect(this, SIGNAL(cellIndexChanged(int, int)),
            dlgLocate, SLOT(setSpinValue(int, int)));

    dlgLocate->show(); // 非模态显示对话框
}

// 点击单元格时，将单元格的行号、列号设置到对话框上
void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    emit cellIndexChanged(index.row(), index.column());
}
