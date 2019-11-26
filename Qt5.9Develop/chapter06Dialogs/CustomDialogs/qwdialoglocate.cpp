#include "qwdialoglocate.h"
#include "ui_qwdialoglocate.h"
#include "mainwindow.h"

#include <QCloseEvent>
#include <QMessageBox>

QWDialogLocate::QWDialogLocate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogLocate)
{
    ui->setupUi(this);
}

QWDialogLocate::~QWDialogLocate()
{
    QMessageBox::information(this, "提示", "单元格定位对话框被删除");
    delete ui;
}

// 窗口关闭事件，关闭时释放本窗口
void QWDialogLocate::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    // 获取父窗口指针
    MainWindow *parWind = static_cast<MainWindow*>(parentWidget());
    parWind->setActLocateEnable(true);	// 启用 actTab_Locate
    parWind->setDlgLocateNull(); // 将窗口指针设置为 NULL
}

// 窗口显示事件
void QWDialogLocate::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    // 获取父窗口指针
    MainWindow *parWind = static_cast<MainWindow*>(parentWidget());
    parWind->setActLocateEnable(false);
}

// 设置SpinBox输入最大值
void QWDialogLocate::setSpinRange(int rowCount, int colCount)
{
    ui->spinBoxRow->setMaximum(rowCount - 1);
    ui->spinBoxColumn->setMaximum(colCount - 1);
}

// 设置SpinBox数值
void QWDialogLocate::setSpinValue(int rowNo, int colNo)
{
    ui->spinBoxRow->setValue(rowNo);
    ui->spinBoxColumn->setValue(colNo);
}

// 定位到单元格，并设置字符串
void QWDialogLocate::on_btnSetText_clicked()
{
    int row = ui->spinBoxRow->value(); // 行号
    int col = ui->spinBoxColumn->value(); // 列号

    MainWindow *parWind = static_cast<MainWindow*>(parentWidget());
    // 设置单元格文字
    parWind->setACellText(row, col, ui->edtCaption->text());


    if (ui->chkBoxRow->isChecked()) { // 行增
        ui->spinBoxRow->setValue(1 + ui->spinBoxRow->value());
    }
    if (ui->chkBoxColumn->isChecked()) { // 列增
        ui->spinBoxColumn->setValue(1 + ui->spinBoxColumn->value());
    }
}
