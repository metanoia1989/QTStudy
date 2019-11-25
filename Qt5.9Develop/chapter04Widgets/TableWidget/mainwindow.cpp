#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QComboBox>
#include <QTextBlock>
#include <QTextDocument>
#include <QDebug>

// 初始化界面
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->splitterMain);

    // 状态栏初始化创建
    labCellIndex = new QLabel("当前单元格坐标：", this);
    labCellIndex->setMinimumWidth(250);

    labCellType = new QLabel("当前单元格类型：", this);
    labCellType->setMinimumWidth(200);

    labStudID = new QLabel("学生ID：", this);
    labStudID->setMinimumWidth(200);

    ui->statusBar->addWidget(labCellIndex);	 // 加到状态栏
    ui->statusBar->addWidget(labCellType);
    ui->statusBar->addWidget(labStudID);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 为一行的单元格创建 Items
void MainWindow::createItemsARow(int rowNo, QString Name, QString Sex,
    QDate birth,  QString Nation, bool isPM, int score)
{
    QTableWidgetItem *item;
    QString str;
    uint StudID = 201605000; // 学号基数

    // 姓名
    // 新建一个 Item，设置单元格type为自定义的MainWindow::ctName
    item = new QTableWidgetItem(Name, ctName);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);	// 文本对齐格式
    StudID += static_cast<uint>(rowNo);	// 学号 = 基数 + 行数
    item->setData(Qt::UserRole, QVariant(StudID));	// 设置studID为data
    ui->tableInfo->setItem(rowNo, colName, item);	// 为单元格设置Item

    // 性别
    QIcon icon;
    if (Sex == "男") {
      icon.addFile(":/images/icons/boy.ico");
    } else {
      icon.addFile(":/images/icons/girl.ico");
    }
    // 新建一个 Item，设置单元格type为自定义的MainWindow::ctSex
    item = new QTableWidgetItem(Name, ctSex);
    item->setIcon(icon);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);	// 文本对齐格式
    ui->tableInfo->setItem(rowNo, colSex, item);	// 为单元格设置Item

    // 出生日期
    // 新建一个 Item，设置单元格type为自定义的MainWindow::ctBirth
    str = birth.toString("yyyy-MM-dd");	// 日期转字符串
    item = new QTableWidgetItem(str, ctBirth);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);	// 文本对齐格式
    ui->tableInfo->setItem(rowNo, colBirth, item);	// 为单元格设置Item

    // 民族
    // 新建一个 Item，设置单元格type为自定义的MainWindow::ctNation
    item = new QTableWidgetItem(Nation, ctNation);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);	// 文本对齐格式
    ui->tableInfo->setItem(rowNo, colNation, item);	// 为单元格设置Item

    // 是否是党员
    // 新建一个 Item，设置单元格type为自定义的MainWindow::ctPartyM
    item = new QTableWidgetItem("党员", ctPartyM);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);	// 文本对齐格式
    if (isPM) {
        item->setCheckState(Qt::Checked);
    } else {
        item->setCheckState(Qt::Unchecked);
    }
    item->setBackgroundColor(Qt::yellow);
    ui->tableInfo->setItem(rowNo, colPartyM, item);	// 为单元格设置Item

    // 分数
    // 新建一个 Item，设置单元格type为自定义的MainWindow::ctScore
    str.setNum(score);
    item = new QTableWidgetItem(str, ctScore);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);	// 文本对齐格式
    ui->tableInfo->setItem(rowNo, colScore, item);	// 为单元格设置Item
}

// 设置表头
void MainWindow::on_btnSetHeader_clicked()
{
    QTableWidgetItem *headerItem;
    QStringList headerText;
    // 表头标题用QStringList来表示
    headerText << "姓 名" << "性 别" << "出生日期" << "名 族" << "分数" << "是否党员";
//    ui->tableInfo->setHorizontalHeaderLabels(headerText);
    // 列数设置为与 headerText的行数相等
    ui->tableInfo->setColumnCount(headerText.count());
    for (int i = 0; i < ui->tableInfo->columnCount(); i++) {
        headerItem = new QTableWidgetItem(headerText.at(i));
        QFont font = headerItem->font(); // 获取原有字体设置
        font.setBold(true);	// 设置为粗体
        font.setPointSize(12);	// 字体大小
        headerItem->setTextColor(Qt::red);	// 字体颜色
        headerItem->setFont(font);	// 设置字体
        // 设置表头单元格的Item
        ui->tableInfo->setHorizontalHeaderItem(i, headerItem);
    }
    // 设置自定义代理组件
    ui->tableInfo->setItemDelegateForColumn(colScore, &spinDelegate);
}

// 设置行数，设置的行数为数据区的行数，不含表头
// 如设置10行，数据区有10行，但是访问行号为0~9
void MainWindow::on_btnSetRows_clicked()
{
    // 设置数据区行数
    ui->tableInfo->setRowCount(ui->spinRowCount->value());
    // 设置交替行背景颜色
    ui->tableInfo->setAlternatingRowColors(ui->chkBoxRowColor->isChecked());
}

// 初始化表格数据
void MainWindow::on_btnIniData_clicked()
{
    QString strName, strSex;
    bool isParty = false;

    QDate birth;
    birth.setDate(1980, 4, 7); // 初始化一个日期
    ui->tableInfo->clearContents(); // 只清除工作区，不清除表头

    int Rows = ui->tableInfo->rowCount(); // 数据区行数
    // 数据区第1行的编号为0，所以范围是0~rowCount()-1
    for (int i = 0; i < Rows; i++) {
        strName = QString::asprintf("学生%d", i); // 学生姓名
        // 分奇数，偶数行设置性别，及其图标
        strSex = (i % 2) == 0 ? "男" : "女";
        // 为某一行创建items
        createItemsARow(i, strName, strSex, birth, "汉族", isParty, 70);
        birth = birth.addDays(20);	// 日期加20天
        isParty = !isParty;
    }
}

// 单元格发生切换时，获取当前单元格的数据以及当前行的学生的学号信息
void MainWindow::on_tableInfo_currentCellChanged(int currentRow,
    int currentColumn, int previousRow, int previousColumn)
{
    Q_UNUSED(previousRow);
    Q_UNUSED(previousColumn);

    // 获取单元格的Item
    QTableWidgetItem *item = ui->tableInfo->item(currentRow, currentColumn);
    if (item == nullptr) return;

    labCellIndex->setText(QString::asprintf("当前单元格坐标：%d 行，%d 列", currentRow, currentColumn));

    int cellType = item->type();	// 获取单元格类型
    labCellType->setText(QString::asprintf("当前单元格类型：%d", cellType));

    // 获取当前行第一列的单元格的item
    item = ui->tableInfo->item(currentRow, colName);
    int ID = item->data(Qt::UserRole).toInt();	// 读取用户自定义数据
    labStudID->setText(QString::asprintf("学生ID：%d", ID));	// 学生ID
}

// 插入一行
void MainWindow::on_btnInsertRow_clicked()
{
    int curRow = ui->tableInfo->currentRow(); // 当前行号
    ui->tableInfo->insertRow(curRow);	// 插入一行，但不会自动为单元格创建items
    createItemsARow(curRow, "新学生", "男",
        QDate::fromString("1990-1-1", "yyyy-M-d"), "苗族", true, 60);
}

// 添加一行
void MainWindow::on_btnAppendRow_clicked()
{
    int curRow = ui->tableInfo->rowCount(); // 最后一行行号
    ui->tableInfo->insertRow(curRow);	// 在表格尾部添加一行
    createItemsARow(curRow, "新生", "女",
        QDate::fromString("2000-1-1", "yyyy-M-d"), "满族", false, 50);
}

// 删除当前行
void MainWindow::on_btnDelCurRow_clicked()
{
    int curRow = ui->tableInfo->currentRow(); // 当前行号
    ui->tableInfo->removeRow(curRow);	// 删除当前行及其items
}

// 自动调节行高
void MainWindow::on_btnAutoHeight_clicked()
{
    ui->tableInfo->resizeRowsToContents();
}

// 自动调节列宽
void MainWindow::on_btnAutoWidth_clicked()
{
    ui->tableInfo->resizeColumnsToContents();
}

// 设置表格内容是否可编辑
void MainWindow::on_chkBoxTabEditable_clicked(bool checked)
{
    if (checked) {
        // 双击或获取焦点后点击，进入编辑状态
        ui->tableInfo->setEditTriggers(QAbstractItemView::DoubleClicked
           |QAbstractItemView::SelectedClicked);
    } else {
        // 不允许编辑
        ui->tableInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

// 设置行表头是否显示
void MainWindow::on_chkBoxHeaderH_clicked(bool checked)
{
    ui->tableInfo->horizontalHeader()->setVisible(checked);
}

// 设置列表头是否显示
void MainWindow::on_chkBoxHeaderV_clicked(bool checked)
{
    ui->tableInfo->verticalHeader()->setVisible(checked);
}

// 设置表格的行是否使用交替底色
void MainWindow::on_chkBoxRowColor_clicked(bool checked)
{
    ui->tableInfo->setAlternatingRowColors(checked);
}

// 设置选择模式为行选择
void MainWindow::on_rBtnSelectRow_clicked()
{
    ui->tableInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
}

// 设置选择模式为单元格选择
void MainWindow::on_rBtnSelectItem_clicked()
{
    ui->tableInfo->setSelectionBehavior(QAbstractItemView::SelectItems);
}

// 遍历表格读取数据
// 将QTableWidget的所有行的内容提取字符串，显示在QPlainTextEdit里
// 需要先设置表头，不然运行会直接中断退出，默认只有两列好像
void MainWindow::on_btnReadToEdit_clicked()
{
    QString str;
    QTableWidgetItem *cellItem;

    ui->textEdit->clear(); // 文本编辑器清空

    // 逐行处理
    for (int i = 0; i < ui->tableInfo->rowCount(); i++) {
        str = QString::asprintf("第 %d 行：", i + 1);
        // 逐列处理，但最后一列是check型，单独处理
        for (int j = 0; j < ui->tableInfo->columnCount() - 1; j++) {
            cellItem = ui->tableInfo->item(i, j);	// 获取单元格的item
            str = str + cellItem->text() + "  ";	// 字符串连接
        }
        cellItem = ui->tableInfo->item(i, colPartyM);	// 最后一列党员
        // 根据check状态显示文字
        if (cellItem->checkState() == Qt::Checked) {
            str += "党员";
        } else {
            str += "群众";
        }
        ui->textEdit->appendPlainText(str);
    }
}
