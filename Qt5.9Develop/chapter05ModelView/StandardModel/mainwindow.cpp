#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>

// 界面初始化，创建数据模型和选择模型，并关联视图组件，关联信号和槽
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    theModel = new QStandardItemModel(2, FixedColumnCount, this); // 数据模型
    theSelection = new QItemSelectionModel(theModel);	// Item选择模型

    // 选择当前单元格变化是的信号与槽
    connect(theSelection, SIGNAL(currentChanged(QModelIndex, QModelIndex)),
            this, SLOT(on_currentChanged(QModelIndex, QModelIndex)));

    // 为tableView设置数据模型
    ui->tableView->setModel(theModel); // 设置数据模型
    ui->tableView->setSelectionModel(theSelection);	// 设置选择模型
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

    setCentralWidget(ui->splitter);

    // 创建状态栏组件
    LabCurFile = new QLabel("当前文件：", this);
    LabCurFile->setMinimumWidth(200);

    LabCellPos = new QLabel("当前单元格：", this);
    LabCellPos->setMinimumWidth(180);
    LabCellPos->setAlignment(Qt::AlignHCenter);

    LabCellText = new QLabel("单元格内容：", this);
    LabCellText->setMinimumWidth(150);

    ui->statusBar->addWidget(LabCurFile);
    ui->statusBar->addWidget(LabCellPos);
    ui->statusBar->addWidget(LabCellText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 从一个StringList获取数据，初始化数据Model
void MainWindow::iniModelFromStringList(QStringList &aFileContent)
{
    int rowCnt = aFileContent.count(); // 文本行数，第一行是标题
    theModel->setRowCount(rowCnt - 1);	// 实际数据行数

    // 设置表头
    QString header = aFileContent.at(0);	// 第1行是表头
    // 一个或多个空格、TAB等分隔符隔开的字符串，分解为一个StringList
    QStringList headerList = header.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    theModel->setHorizontalHeaderLabels(headerList);	// 设置表头文字

    // 设置表格数据
    int j;
    QStandardItem *aItem;
    for (int i = 1; i < rowCnt; i++) {
        QString aLineText = aFileContent.at(i); // 获取数据区的一行
        // 一个或多个空格、TAB等分隔符隔开的字符串，分解为一个StringList
        QStringList tmpList = aLineText.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        // tmpList的行数等于FixedColumnCountg，固定的
        // 不包含最后一行
        for (j = 0; j < FixedColumnCount - 1; i++) {
            aItem = new QStandardItem(tmpList.at(j)); // 创建Item
            theModel->setItem(i - 1, j, aItem); // 为模型的某个行列位置设置Item
        }
        // 最后一行的设置
        aItem = new QStandardItem(headerList.at(j)); // 最后一列是 Checkable，需要设置
        aItem->setCheckable(true);
        if (tmpList.at(j) == "0") {
            aItem->setCheckState(Qt::Unchecked);	 // 根据数据设置check状态
        } else {
            aItem->setCheckState(Qt::Checked);
        }
        theModel->setItem(i - 1, j, aItem);

    }
}

// 当前选择的单元格发生变化时，更新状态栏的信息显示
// 与项选择模型theSelection的currentChanged()信号关联
void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);

    if (current.isValid()) {
        // 显示模型索引的行和列号
        LabCellPos->setText(QString::asprintf("当前单元格：%d行,%d列",
                              current.row(), current.column()));
        QStandardItem *aItem;
        aItem = theModel->itemFromIndex(current);	// 从模型索引获得Item
        // 显示Item的内容
        this->LabCellText->setText("单元格内容：" + aItem->text());

        QFont font = aItem->font(); // 获取Item的字体
        // 更新actFontBold的check状态
        ui->actFontBold->setChecked(font.bold());
    }
}

// 打开文件
void MainWindow::on_actOpen_triggered()
{
    // 获取应用程序的路径
    QString curPath = QCoreApplication::applicationDirPath();
    // 调用打开文件对话框打开一个文件
    QString aFileName = QFileDialog::getOpenFileName(this, "打开一个文件", curPath
                         , "仅数据文件(*.txt);;所有文件(*.*)");
    if (aFileName.isEmpty()) {
        return; // 未选择文件，直接退出
    }

    QStringList fFileContent;// 文件内容字符串列表
    QFile aFile(aFileName);	// 以文件方式读出
    if (aFile.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QTextStream aStream(&aFile); // 用文本流读取文件
        ui->plainTextEdit->clear();
        while (!aStream.atEnd()) {
            QString str = aStream.readLine(); // 读取文件的一行
            ui->plainTextEdit->appendPlainText(str); // 添加到文本框显示
            fFileContent.append(str);	// 添加到 StringList
        }
        aFile.close(); // 关闭文件

        // 状态栏显示
        this->LabCurFile->setText("当前文件：" + aFileName);
        ui->actAppend->setEnabled(true);
        ui->actInsert->setEnabled(true);
        ui->actDelete->setEnabled(true);
        ui->actSave->setEnabled(true);

        // 从StringList的内容初始化数据模型
        iniModelFromStringList(fFileContent);
    }
}

// 保存为文件
void MainWindow::on_actSave_triggered()
{
    // 获取应用程序的路径
    QString curPath = QCoreApplication::applicationDirPath();
    // 调用打开文件对话框打开一个文件
    QString aFileName = QFileDialog::getOpenFileName(this, "选择一个文件", curPath
                         , "井斜数据文件(*.txt);;所有文件(*.*)");
    if (aFileName.isEmpty()) {
        return; // 未选择文件，直接退出
    }

    QFile aFile(aFileName);
    if (!(aFile.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate))) {
        return; // 以读写、覆盖原有内容方式打开文件
    }

    QTextStream aStream(&aFile);	// 用文本流读取文件
    QStandardItem *aItem;
    QString str;

    ui->plainTextEdit->clear();

    // 获取表头文字
    int i, j;
    for (i = 0; i < theModel->columnCount(); i++) {
        aItem = theModel->horizontalHeaderItem(i);	// 获取表头的项数据
        str = str + aItem->text() + "\t\t";
    }
    aStream << str << "\n"; // 文件里加入换行符 \n
    ui->plainTextEdit->appendPlainText(str);

    // 获取数据区文字
    for (i = 0; i < theModel->rowCount(); i++) {
        str = "";
        for (j = 0; j < theModel->columnCount() - 1; j++) {
            aItem = theModel->item(i, j);
            str = str + aItem->text() + QString::asprintf("\t\t");
        }

        aItem = theModel->item(i, j);	// 最后一列是逻辑型
        if (aItem->checkState() == Qt::Checked) {
            str += "1";
        } else {
            str += "0";
        }

        ui->plainTextEdit->appendPlainText(str);
        aStream << str << "\n";
    }
}

// 在表格最后添加行
void MainWindow::on_actAppend_triggered()
{
    QList<QStandardItem*> aItemList;	// 容器类
    QStandardItem *aItem;
    // 不包含最后1列
    for (int i = 0; i < FixedColumnCount - 1; i++) {
        aItem = new QStandardItem("0"); // 创建Item
        aItemList << aItem; // 添加到容器
    }

    // 获取最后一列的表头文字
    QString str = theModel->headerData(theModel->columnCount() -1 ,
                   Qt::Horizontal, Qt::DisplayRole).toString();
    aItem = new QStandardItem(str);	// 创建“测井取样”Item
    aItem->setCheckable(true);
    aItemList << aItem;	// 添加到容器

    // 插入一行，需要每个Cell的Item
    theModel->insertRow(theModel->rowCount(), aItemList);
    // 创建最后一行的ModelIndex
    QModelIndex curIndex = theModel->index(theModel->rowCount() - 1, 0);
    theSelection->clearSelection(); // 清空选择项
    // 设置刚插入的行作为当前选择行
    theSelection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
}

// 插入行
void MainWindow::on_actInsert_triggered()
{
    QList<QStandardItem*> aItemList;	// 容器类
    QStandardItem *aItem;
    // 不包含最后1列
    for (int i = 0; i < FixedColumnCount - 1; i++) {
        aItem = new QStandardItem("0"); // 创建Item
        aItemList << aItem; // 添加到容器
    }

    // 获取最后一列的表头文字
    QString str = theModel->headerData(theModel->columnCount() -1 ,
                   Qt::Horizontal, Qt::DisplayRole).toString();
    aItem = new QStandardItem(str);	// 创建“测井取样”Item
    aItem->setCheckable(true);
    aItemList << aItem;	// 添加到容器

    // 获取当前选中项的模型索引
    QModelIndex curIndex = theSelection->currentIndex();
    // 在当前行的前面插入一行
    theModel->insertRow(curIndex.row(), aItemList);
    theSelection->clearSelection(); // 清空选择项
    // 设置刚插入的行作为当前选择行
    theSelection->setCurrentIndex(curIndex, QItemSelectionModel::Select);

}

// 删除行
void MainWindow::on_actDelete_triggered()
{
    QModelIndex curIndex = theSelection->currentIndex();

    if (curIndex.row() == theModel->rowCount() - 1) {
        // 是最后一行，删除最后一行
        theModel->removeRow(curIndex.row());
    } else {
        // 删除一行，并重新设置当前选择行
        theModel->removeRow(curIndex.row());
        theSelection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
    }
}

// 数据导出到PlainTextEdit显示
void MainWindow::on_actModelData_triggered()
{
    ui->plainTextEdit->clear();
    QStandardItem *aItem;
    QString str;

    ui->plainTextEdit->clear();

    // 获取表头文字
    int i, j;
    for (i = 0; i < theModel->columnCount(); i++) {
        aItem = theModel->horizontalHeaderItem(i);	// 获取表头的项数据
        str = str + aItem->text() + "\t\t";
    }
    ui->plainTextEdit->appendPlainText(str);

    // 获取数据区文字
    for (i = 0; i < theModel->rowCount(); i++) {
        str = "";
        for (j = 0; j < theModel->columnCount() - 1; j++) {
            aItem = theModel->item(i, j);
            str = str + aItem->text() + QString::asprintf("\t\t");
        }

        aItem = theModel->item(i, j);	// 最后一列是逻辑型
        if (aItem->checkState() == Qt::Checked) {
            str += "1";
        } else {
            str += "0";
        }

        ui->plainTextEdit->appendPlainText(str);
    }
}

// 文字左对齐
void MainWindow::on_actAlignLeft_triggered()
{
    if (!theSelection->hasSelection()) {
        return;
    }

    // 获取选择单元格的模型索引列表
    QModelIndexList selectedIndex = theSelection->selectedIndexes();

    for (int i = 0; i < selectedIndex.count(); i++) {
        // 获取一个模型索引
        QModelIndex aIndex = selectedIndex.at(i);
        // 获取项数据
        QStandardItem *aItem = theModel->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignLeft);
    }
}

// 文字居中对齐
void MainWindow::on_actAlignCenter_triggered()
{
    if (!theSelection->hasSelection()) {
        return;
    }

    // 获取选择单元格的模型索引列表
    QModelIndexList selectedIndex = theSelection->selectedIndexes();

    for (int i = 0; i < selectedIndex.count(); i++) {
        // 获取一个模型索引
        QModelIndex aIndex = selectedIndex.at(i);
        // 获取项数据
        QStandardItem *aItem = theModel->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignHCenter);
    }
}

// 文字右对齐
void MainWindow::on_actAlignRight_triggered()
{
    if (!theSelection->hasSelection()) {
        return;
    }

    // 获取选择单元格的模型索引列表
    QModelIndexList selectedIndex = theSelection->selectedIndexes();

    for (int i = 0; i < selectedIndex.count(); i++) {
        // 获取一个模型索引
        QModelIndex aIndex = selectedIndex.at(i);
        // 获取项数据
        QStandardItem *aItem = theModel->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignRight);
    }
}

// 设置文字为粗体
void MainWindow::on_actFontBold_triggered(bool checked)
{
    if (!theSelection->hasSelection()) {
        return;
    }

    // 获取选择单元格的模型索引列表
    QModelIndexList selectedIndex = theSelection->selectedIndexes();

    for (int i = 0; i < selectedIndex.count(); i++) {
        // 获取一个模型索引
        QModelIndex aIndex = selectedIndex.at(i);
        // 获取项数据
        QStandardItem *aItem = theModel->itemFromIndex(aIndex);
        QFont font = aItem->font();
        font.setBold(checked);
        aItem->setFont(font);
    }
}
