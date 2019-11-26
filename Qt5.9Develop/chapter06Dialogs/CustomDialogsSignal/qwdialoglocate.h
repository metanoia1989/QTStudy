#ifndef QWDIALOGLOCATE_H
#define QWDIALOGLOCATE_H

#include <QDialog>

namespace Ui {
class QWDialogLocate;
}

class QWDialogLocate : public QDialog
{
    Q_OBJECT

public:
    explicit QWDialogLocate(QWidget *parent = nullptr);
    ~QWDialogLocate();

    void setSpinRange(int rowCount, int colCount);	// 设置最大值

private slots:
    void on_btnSetText_clicked();

public slots:
    void setSpinValue(int rowNo, int colNo);	// 响应主窗口信号，设置 spinBox 的值

signals:
    // 释放信号，定位单元格，并设置文字
    void changeCellText(int row, int column, QString &text);
    // 是否信号，改变 action 的 enable
    void changeActionEnable(bool en);

private:
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);

    Ui::QWDialogLocate *ui;
};

#endif // QWDIALOGLOCATE_H
