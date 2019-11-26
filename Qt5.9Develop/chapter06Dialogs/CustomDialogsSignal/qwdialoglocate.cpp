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

// 窗口关闭事件，释放信号使 actTab_Locate 能用
void QWDialogLocate::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    emit changeActionEnable(true);
}

// 窗口显示事件，释放信号使 actTab_Locate 不能用
void QWDialogLocate::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    emit changeActionEnable(false);
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
    QString text = ui->edtCaption->text();

    // 释放信号，
    emit changeCellText(row, col, text);

    // 设置单元格文字
    if (ui->chkBoxRow->isChecked()) { // 行增
        ui->spinBoxRow->setValue(1 + ui->spinBoxRow->value());
    }
    if (ui->chkBoxColumn->isChecked()) { // 列增
        ui->spinBoxColumn->setValue(1 + ui->spinBoxColumn->value());
    }
}
