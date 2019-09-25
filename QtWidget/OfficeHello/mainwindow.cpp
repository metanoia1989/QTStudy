#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myexcel = new QAxObject("Excel.Application");
    myworks = myexcel->querySubObject("WorkBooks");	// 获取工作簿
    myworks->dynamicCall("Add");	// 添加工作簿
    workbook= myexcel->querySubObject("ActiveWorkBook");	// 获取当前活动工作簿
    mysheets = workbook->querySubObject("Sheets");	// 获取电子表格集

    myword = new QAxObject("Word.Application");
    mydocs = myword->querySubObject("Documents");	// 获取文档集
    mydocs->dynamicCall("Add(void)");	// 添加一个文档
    document = myword->querySubObject("ActiveDocument");	// 指向当前活动文档
    paragraph = myword->querySubObject("Selection");	// 指向当前选中文本
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 写 Excel
void MainWindow::on_writeExcelPushButton_clicked()
{
    mysheets->dynamicCall("Add");	// 添加一个表
    QAxObject *sheet = workbook->querySubObject("ActiveSheet");	// 指向当前活动表格
    sheet->setProperty("Name", "我爱Qt");	// 给表格命名
    QAxObject *cell = sheet->querySubObject("Range(QVariant, QVariant)", "C3");	// 指向C3单元格
    QString inStr = ui->InExcelLineEdit->text();
    cell->dynamicCall("SetValue(const QVariant&)", QVariant(inStr));	// 向单元格写入内容

    sheet = mysheets->querySubObject("Item(int)", 2);	// 指向第二个表格
    sheet->setProperty("Name", "Hello Qt");
    cell = sheet->querySubObject("Range(QVariant, QVariant)", "B5");
    cell->dynamicCall("SetValue(const QVariant&)",
        "F:\\WORKSPACE\\QT\\QTStudy\\QtWidget\\OfficeHello\\我爱Qt5.xls");	// 保存 Excel
    workbook->dynamicCall("Close()");
    myexcel->dynamicCall("Quit()");
    QMessageBox::information(this, tr("完毕"), tr("Excel工作表已保存。"));
    ui->writeExcelPushButton->setEnabled(false);
    ui->readExcelPushButton->setEnabled(true);
}

// 读 Excel
void MainWindow::on_readExcelPushButton_clicked()
{
    myexcel = new QAxObject("Excel.Application");
    myworks = myexcel->querySubObject("WorkBooks");
    myworks->dynamicCall("Open(const QString&)",
        "F:\\WORKSPACE\\QT\\QTStudy\\QtWidget\\OfficeHello\\我爱Qt5.xls");	// 打开 Excel
    workbook = myexcel->querySubObject("ActiveWorkBook");
    mysheets = workbook->querySubObject("WorkSheet");
    QAxObject *sheet = workbook->querySubObject("Sheets(int)", 1);
    QAxObject *cell = sheet->querySubObject("Range(QVariant, QVariant)", "C3");
    QString outStr = cell->dynamicCall("Value2()").toString();	// 读出C3单元格数据
    ui->OutExcelLabel->setText(outStr);

    sheet = workbook->querySubObject("Sheet(int)", 2);	// 定位到第二张表格
    cell = sheet->querySubObject("Range(QVariant, QVariant)", "B5");
    outStr = cell->dynamicCall("Value2()").toString();
    workbook->dynamicCall("Close()");
    myexcel->dynamicCall("Quit()");
    QMessageBox::information(this, tr("消息"), outStr);
    ui->writeExcelPushButton->setEnabled(true);
    ui->readExcelPushButton->setEnabled(false);
}

// 写 Word
void MainWindow::on_writeWordPushButton_clicked()
{
    QString inStr = ui->InWordLineEdit->text();
    paragraph->dynamicCall("TypeText(const QString&)", inStr);	// 写入从界面文档框获取的文本
    paragraph->dynamicCall("TypeText(const QVariant&)", QVariant("\nHello!I love Qt."));	// 写入指定文本
    document->dynamicCall("SaveAs(const QString&)",
        "F:\\WORKSPACE\\QT\\QTStudy\\QtWidget\\OfficeHello\\我爱Qt5.doc");	//	 保存文档
    delete paragraph;
    paragraph = nullptr;
    document->dynamicCall("Close()");
    myword->dynamicCall("Quit()");
    QMessageBox::information(this, tr("完毕"), tr("Word文档已保存。"));
    ui->writeWordPushButton->setEnabled(false);
    ui->readWordPushButton->setEnabled(true);
}

// 读 Word
void MainWindow::on_readWordPushButton_clicked()
{
    myword = new QAxObject("Word.Application");
    mydocs = myexcel->querySubObject("Documents");
    mydocs->dynamicCall("Open(const QString&)",
        "F:\\WORKSPACE\\QT\\QTStudy\\QtWidget\\OfficeHello\\我爱Qt5.doc");	// 打开文档
    document = myword->querySubObject("ActiveDocument");
    paragraph = document->querySubObject("Range()");	// 指向当前文本
    QString outStr = paragraph->property("Text").toString();	// 读出文本
    ui->OutWordLabel->setText(outStr.split("H").at(0));
    paragraph = document->querySubObject("Range(QVariant, QVariant)", 14, 30);
    outStr = paragraph->property("Text").toString();
    delete  paragraph;
    paragraph = nullptr;
    document->dynamicCall("Close()");
    myword->dynamicCall("Quit()");
    QMessageBox::information(this, tr("消息"), outStr);
    ui->writeWordPushButton->setEnabled(true);
    ui->readWordPushButton->setEnabled(false);
}
