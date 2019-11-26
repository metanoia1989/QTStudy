#ifndef QWDIALOGSIZE_H
#define QWDIALOGSIZE_H

#include <QDialog>

namespace Ui {
class QWDialogSize;
}

class QWDialogSize : public QDialog
{
    Q_OBJECT

public:
    explicit QWDialogSize(QWidget *parent = nullptr);
    ~QWDialogSize();

    // 窗体上的组件都是私有成员，外界无法直接访问，通过接口函数暴露数据
    int rowCount();	// 获取对话框输入的行数
    int columnCount();	// 获取对话框输入的列数
    void setRowColumn(int row, int column);	// 初始化对话框上两个SpinBox的值

private:
    Ui::QWDialogSize *ui;
};

#endif // QWDIALOGSIZE_H
