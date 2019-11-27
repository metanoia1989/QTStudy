#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDataStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    theModel = new QStandardItemModel(5, FixedColumnCount, this);	// 创建数据模型
    QStringList headerList;
    headerList<<"Depth"<<"Measured Depth"<<"Direction"<<"Offset"<<"Quality"<<"Sampled";
    theModel->setHorizontalHeaderLabels(headerList);

    theSelection = new QItemSelectionModel(theModel); // Item选择模型
    connect(theSelection, SIGNAL(currentChanged(QModelIndex, QModelIndex)),
            this, SLOT(on_currentChanged(QModelIndex, QModelIndex)));

    // 为 tableView 设置数据模型
    ui->tableView->setModel(theModel);	// 设置数据模型
    ui->tableView->setSelectionModel(theSelection); // 设置选择模型

    // 为各列设置自定义代理组件
    ui->tableView->setItemDelegateForColumn(0, &intSpinDelegate);	// 测深，整数
    ui->tableView->setItemDelegateForColumn(1, &floatSpinDelegate);	// 浮点数
    ui->tableView->setItemDelegateForColumn(2, &floatSpinDelegate);	// 浮点数
    ui->tableView->setItemDelegateForColumn(3, &floatSpinDelegate);	// 浮点数
    ui->tableView->setItemDelegateForColumn(4, &comboBoxDelegate);	// ComboBox选择型

    resetTable(5);	// 表格复位
    setCentralWidget(ui->tabWidget);

    // 创建状态栏组件
    LabCellPos = new QLabel("当前单元格：", this);
    LabCellPos->setMinimumWidth(180);
    LabCellPos->setAlignment(Qt::AlignHCenter);

    LabCellText = new QLabel("单元格内容：", this);
    LabCellText->setMinimumWidth(200);

    ui->statusBar->addWidget(LabCellPos);
    ui->statusBar->addWidget(LabCellText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 表格复位，先删除所有行，再设置新的行数，表头不变
void MainWindow::resetTable(int aRowCount)
{
    // 删除所有行
    theModel->removeRows(0, theModel->rowCount());
    theModel->setRowCount(aRowCount);	// 设置新的行数

    QString str = theModel->headerData(theModel->columnCount()-1,
                    Qt::Horizontal, Qt::DisplayRole).toString();

    // 设置最后一列
    for (int i = 0; i < theModel->rowCount(); i++) {
        // 获取模型索引
        QModelIndex index = theModel->index(i, FixedColumnCount - 1);
        QStandardItem *aItem = theModel->itemFromIndex(index);	// 获取item
        aItem->setCheckable(true);
        aItem->setData(str, Qt::DisplayRole);
        aItem->setEditable(false);	// 不可编辑
    }
}

// 将模型数据保存为Qt预定义编码的数据文件
bool MainWindow::saveDataAsStream(QString &aFileName)
{
    QFile aFile(aFileName);
    if (!aFile.open(QIODevice::WriteOnly|QIODevice::Truncate)) {
        return false;
    }

    QDataStream aStream(&aFile);
    aStream.setVersion(QDataStream::Qt_5_12); // 设置版本号，写入和读取的版本号要兼容

    qint16 rowCount = static_cast<qint16>(theModel->rowCount());	// 数据模型行数
    qint16 colCount = static_cast<qint16>(theModel->columnCount());	// 数据模型列数

    aStream << rowCount; // 写入文件流，行数
    aStream << colCount; // 写入文件流，列数

    // 获取表头文字
    for (int i = 0; i < theModel->columnCount(); i++) {
        QString str = theModel->horizontalHeaderItem(i)->text(); // 获取表头文字
        aStream << str;	// 字符串写入文件流，Qt 预定编码方式
    }

    // 获取数据区的数据
    for (int i = 0; i < theModel->rowCount(); i++) {
        QStandardItem *aItem = theModel->item(i ,0);	// 测深
        qint16 ceShen = static_cast<qint16>(aItem->data(Qt::DisplayRole).toInt());
        aStream << ceShen;	// 写入文件流，qint16

        aItem = theModel->item(i ,1);	// 垂深
        qreal chuiShen = static_cast<qreal>(aItem->data(Qt::DisplayRole).toFloat());
        aStream << chuiShen;	// 写入文件流，qreal

        aItem = theModel->item(i ,2);	// 方位
        qreal fangwei = static_cast<qreal>(aItem->data(Qt::DisplayRole).toFloat());
        aStream << fangwei;	// 写入文件流，qreal

        aItem = theModel->item(i ,3);	// 位移
        qreal weiYi = static_cast<qreal>(aItem->data(Qt::DisplayRole).toFloat());
        aStream << weiYi;	// 写入文件流，qreal

        aItem = theModel->item(i ,4);	// 固井质量
        QString zhiLiang = aItem->data(Qt::DisplayRole).toString();
        aStream << zhiLiang;	// 写入文件流，字符串

        aItem = theModel->item(i ,5);	// 测井
        bool quYang = (aItem->checkState() == Qt::Checked);
        aStream << quYang;	// 写入文件流，bool
    }
    aFile.close();
    return true;
}

// 从Qt预定义流文件读入数据
bool MainWindow::openDataAsStream(QString &aFileName)
{
    QFile aFile(aFileName);
    if (!aFile.open(QIODevice::ReadOnly)) {
        return false;
    }
    QDataStream aStream(&aFile);
    aStream.setVersion(QDataStream::Qt_5_12);	// 设置流文件版本号

    qint16 rowCount, colCount;
    aStream >> rowCount; // 读取行数
    aStream >> colCount; // 列数

    this->resetTable(rowCount);	// 表格复位

    // 获取表头文字
    QString str;
    for (int i = 0; i < colCount; i++) {
        aStream >> str;	// 读取表头字符串
    }

    // 获取数据区文字
    qint16 ceShen;	// 测深
    qreal chuiShen;	// 垂深
    qreal fangwei;	// 方位
    qreal weiYi;	// 位移
    QString zhiLiang;	// 质量
    bool quYang;	// 测井
    QStandardItem *aItem;
    QModelIndex index;

    for (int i = 0; i < rowCount; i++) {
        aStream >> ceShen;	// 读取测试，qint16
        index = theModel->index(i, 0);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(ceShen, Qt::DisplayRole);

        aStream >> chuiShen;	// 垂深，qreal
        index = theModel->index(i, 1);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(chuiShen, Qt::DisplayRole);

        aStream >> fangwei;	// 方位，qreal
        index = theModel->index(i, 2);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(fangwei, Qt::DisplayRole);

        aStream >> weiYi;	// 位移，qreal
        index = theModel->index(i, 3);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(weiYi, Qt::DisplayRole);

        aStream >> zhiLiang;	// 固井质量，QString
        index = theModel->index(i, 4);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(zhiLiang, Qt::DisplayRole);

        aStream >> quYang;	// bool
        index = theModel->index(i, 5);
        aItem = theModel->itemFromIndex(index);
        if (quYang) {
            aItem->setCheckState(Qt::Checked);
        } else {
            aItem->setCheckState(Qt::Unchecked);
        }
    }
    aFile.close();
    return true;
}

// 保存为纯二进制文件
bool MainWindow::saveBinaryFile(QString &aFileName)
{
    QFile aFile(aFileName);
    if (!aFile.open(QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream aStream(&aFile);
    aStream.setByteOrder(QDataStream::LittleEndian); // Windows 平台，小端字节序

    qint16 rowCount = static_cast<qint16>(theModel->rowCount());
    qint16 colCount = static_cast<qint16>(theModel->columnCount());

    // 写入文件流
    aStream.writeRawData(reinterpret_cast<char*>(&rowCount), sizeof (qint16));
    aStream.writeRawData(reinterpret_cast<char*>(&colCount), sizeof (qint16));

    // 获取表头文字
    QByteArray btArray;
    QStandardItem *aItem;
    for (int i = 0; i < theModel->columnCount(); i++) {
        aItem = theModel->horizontalHeaderItem(i);	// 获取表头item
        QString str = aItem->text(); // 获取表头文字
        btArray = str.toUtf8(); // 转换为字符数组
        // 写入文件流，长度uint型，然后是字符串内容
        aStream.writeBytes(btArray, static_cast<uint>(btArray.length()));
    }

    // 获取数据区文字
    qint8 yes = 1, no = 0;	// 分别代表逻辑值 true 和 false
    for (int i = 0; i < theModel->rowCount(); i++) {
        aItem = theModel->item(i, 0);	// 测深
        qint16 ceShen = static_cast<qint16>(aItem->data(Qt::DisplayRole).toInt());
        aStream.writeRawData(reinterpret_cast<char*>(&ceShen), sizeof (qint16)); // 写入文件流

        aItem = theModel->item(i, 1);	// 垂深
        qreal chuiShen = static_cast<qreal>(aItem->data(Qt::DisplayRole).toFloat());
        aStream.writeRawData(reinterpret_cast<char*>(&chuiShen), sizeof (qreal)); // 写入文件流

        aItem = theModel->item(i, 2);	// 方位
        qreal fangwei = static_cast<qreal>(aItem->data(Qt::DisplayRole).toFloat());
        aStream.writeRawData(reinterpret_cast<char*>(&fangwei), sizeof (qreal)); // 写入文件流

        aItem = theModel->item(i, 3);	// 位移
        qreal weiYi = static_cast<qreal>(aItem->data(Qt::DisplayRole).toFloat());
        aStream.writeRawData(reinterpret_cast<char*>(&weiYi), sizeof (qreal)); // 写入文件流

        aItem = theModel->item(i, 4);	// 固井质量
        QString zhiLiang = aItem->data(Qt::DisplayRole).toString();
        btArray = zhiLiang.toUtf8();
        aStream.writeBytes(btArray, static_cast<uint>(btArray.length()));

        aItem = theModel->item(i, 5);	// 测井取样
        bool quYang = aItem->checkState() == Qt::Checked;
        if (quYang) {
            aStream.writeRawData(reinterpret_cast<char*>(&yes), sizeof (qint8));
        } else {
            aStream.writeRawData(reinterpret_cast<char*>(&no), sizeof (qint8));
        }
    }
    aFile.close();
    return true;
}

// 打开二进制文件
bool MainWindow::openBinaryFile(QString &aFileName)
{
    QFile aFile(aFileName);
    if (!aFile.open(QIODevice::ReadOnly)) {
        return false;
    }

    QDataStream aStream(&aFile);
    aStream.setByteOrder(QDataStream::LittleEndian);

    qint16 rowCount, colCount;
    aStream.readRawData(reinterpret_cast<char*>(&rowCount), sizeof (qint16));
    aStream.readRawData(reinterpret_cast<char*>(&colCount), sizeof (qint16));
    this->resetTable(rowCount);

    // 获取表头文字，但是不利用
    char *buf;
    uint strLen;	// quint32
    for (int i = 0; i < colCount; i++) {
        aStream.readBytes(buf, strLen);	// 同时读取字符串长度，和字符串内容
        QString str = QString::fromLocal8Bit(buf, strLen);	// 可处理汉字
    }

    // 获取数据区数据
    qint16 ceShen;	// 测深
    qreal chuiShen;	// 垂深
    qreal fangwei;	// 方位
    qreal weiYi;	// 位移
    QString zhiLiang;	// 质量
    qint8 quYang;	// 测井 分别代表逻辑值 true 和 false
    QStandardItem *aItem;
    QModelIndex index;

    for (int i = 0; i < rowCount; i++) {
        // 测深
        aStream.readRawData(reinterpret_cast<char*>(&ceShen), sizeof (qint16));
        index = theModel->index(i, 0);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(ceShen, Qt::DisplayRole);

        // 垂深，qreal
        aStream.readRawData(reinterpret_cast<char*>(&chuiShen), sizeof (qreal));
        index = theModel->index(i, 1);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(chuiShen, Qt::DisplayRole);

        // 方位，qreal
        aStream.readRawData(reinterpret_cast<char*>(&fangwei), sizeof (qreal));
        index = theModel->index(i, 2);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(fangwei, Qt::DisplayRole);

        // 位移，qreal
        aStream.readRawData(reinterpret_cast<char*>(&weiYi), sizeof (qreal));
        index = theModel->index(i, 3);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(weiYi, Qt::DisplayRole);

        // 固井质量，QString
        aStream.readBytes(buf, strLen);
        zhiLiang = QString::fromLocal8Bit(buf, strLen);
        index = theModel->index(i, 4);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(zhiLiang, Qt::DisplayRole);

        // 测井取样
        aStream.readRawData(reinterpret_cast<char*>(&quYang), sizeof (qint8));
        index = theModel->index(i, 5);
        aItem = theModel->itemFromIndex(index);
        if (quYang == 1) {
            aItem->setCheckState(Qt::Checked);
        } else {
            aItem->setCheckState(Qt::Unchecked);
        }
    }
    aFile.close();
    return true;
}

void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);

    if (current.isValid()) {
        LabCellPos->setText(QString::asprintf("当前单元格：%d行，%d列",
                      current.row(), current.column()));
        QStandardItem *aItem;
        aItem = theModel->itemFromIndex(current);	// 从模型索引获得Item
        this->LabCellText->setText("单元格内容：" + aItem->text());

        QFont font = aItem->font();
        ui->actFontBold->setChecked(font.bold());
    }
}

// 打开stm文件
void MainWindow::on_actOpen_triggered()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getOpenFileName(this, tr("打开一个文件"), curPath,
                             "流数据文件(*.stm)");

    if (aFileName.isEmpty()) {
        return;
    }

    // 打开为流数据文件
    if (openDataAsStream(aFileName)) {
        QMessageBox::information(this, "提示消息", "文件已经打开！");
    }
}

// 保存stm文件
void MainWindow::on_actSave_triggered()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getSaveFileName(this, tr("选择保存文件"), curPath,
                             "Qt预定义编码数据文件(*.stm)");

    if (aFileName.isEmpty()) {
        return;
    }

    // 保存为流数据文件
    if (saveDataAsStream(aFileName)) {
        QMessageBox::information(this, "提示消息", "文件已经成功保存！");
    }
}

void MainWindow::on_actAppend_triggered()
{ //添加行
    QList<QStandardItem*>    aItemList; //容器类
    QStandardItem   *aItem;
    QString str;
    for(int i=0;i<FixedColumnCount-2;i++)
    {
        aItem=new QStandardItem("0"); //创建Item
        aItemList<<aItem;   //添加到容器
    }
    aItem=new QStandardItem("优"); //创建Item
    aItemList<<aItem;   //添加到容器

    str=theModel->headerData(theModel->columnCount()-1,Qt::Horizontal,Qt::DisplayRole).toString();
    aItem=new QStandardItem(str); //创建Item
    aItem->setCheckable(true);
    aItem->setEditable(false);
    aItemList<<aItem;   //添加到容器

    theModel->insertRow(theModel->rowCount(),aItemList); //插入一行，需要每个Cell的Item
    QModelIndex curIndex=theModel->index(theModel->rowCount()-1,0);//创建最后一行的ModelIndex
    theSelection->clearSelection();
    theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);
}

void MainWindow::on_actInsert_triggered()
{//插入行
    QList<QStandardItem*>    aItemList;  //QStandardItem的容器类
    QStandardItem   *aItem;
    QString str;
    for(int i=0;i<FixedColumnCount-2;i++)
    {
        aItem=new QStandardItem("0"); //新建一个QStandardItem
        aItemList<<aItem;//添加到容器类
    }
    aItem=new QStandardItem("优"); //新建一个QStandardItem
    aItemList<<aItem;//添加到容器类

    str=theModel->headerData(theModel->columnCount()-1,Qt::Horizontal,Qt::DisplayRole).toString();
    aItem=new QStandardItem(str); //创建Item
    aItem->setCheckable(true);
    aItem->setEditable(false);
    aItemList<<aItem;//添加到容器类
    QModelIndex curIndex=theSelection->currentIndex();
    theModel->insertRow(curIndex.row(),aItemList);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);
}

void MainWindow::on_actDelete_triggered()
{ //删除行
    QModelIndex curIndex=theSelection->currentIndex();
    if (curIndex.row()==theModel->rowCount()-1)//(curIndex.isValid())
        theModel->removeRow(curIndex.row());
    else
    {
        theModel->removeRow(curIndex.row());
        theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);
    }
}


void MainWindow::on_actModelData_triggered()
{

}

void MainWindow::on_actAlignCenter_triggered()
{
    if (!theSelection->hasSelection())
        return;

    QModelIndexList selectedIndix=theSelection->selectedIndexes();

    QModelIndex aIndex;
    QStandardItem   *aItem;

    for (int i=0;i<selectedIndix.count();i++)
    {
        aIndex=selectedIndix.at(i);
        aItem=theModel->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignHCenter);
    }
}

void MainWindow::on_actFontBold_triggered(bool checked)
{
    if (!theSelection->hasSelection())
        return;

    QModelIndexList selectedIndix=theSelection->selectedIndexes();

    QModelIndex aIndex;
    QStandardItem   *aItem;
    QFont   font;

    for (int i=0;i<selectedIndix.count();i++)
    {
        aIndex=selectedIndix.at(i);
        aItem=theModel->itemFromIndex(aIndex);
        font=aItem->font();
        font.setBold(checked);
        aItem->setFont(font);
    }

}

void MainWindow::on_actAlignLeft_triggered()
{
    if (!theSelection->hasSelection())
        return;

    QModelIndexList selectedIndix=theSelection->selectedIndexes();

    QModelIndex aIndex;
    QStandardItem   *aItem;

    for (int i=0;i<selectedIndix.count();i++)
    {
        aIndex=selectedIndix.at(i);
        aItem=theModel->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignLeft);
    }
}

void MainWindow::on_actAlignRight_triggered()
{
    if (!theSelection->hasSelection())
        return;

    QModelIndexList selectedIndix=theSelection->selectedIndexes();

    QModelIndex aIndex;
    QStandardItem   *aItem;

    for (int i=0;i<selectedIndix.count();i++)
    {
        aIndex=selectedIndix.at(i);
        aItem=theModel->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignRight);
    }
}


// 表格复位
void MainWindow::on_actTabReset_triggered()
{
    resetTable(10);
}

// 打开二进制文件
void MainWindow::on_actOpenBin_triggered()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getOpenFileName(this, tr("打开一个文件"), curPath,
                             "二进制数据文件(*.dat)");

    if (aFileName.isEmpty()) {
        return;
    }

    // 打开为流数据文件
    if (openBinaryFile(aFileName)) {
        QMessageBox::information(this, "提示消息", "文件已经打开！");
    }
}

// 保存二进制文件
void MainWindow::on_actSaveBin_triggered()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getSaveFileName(this, tr("选择保存文件"), curPath,
                             "二进制数据文件(*.dat)");

    if (aFileName.isEmpty()) {
        return;
    }

    // 保存为流数据文件
    if (saveBinaryFile(aFileName)) {
        QMessageBox::information(this, "提示消息", "文件已经成功保存！");
    }
}
