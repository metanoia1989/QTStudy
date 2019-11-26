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
    void setSpinValue(int rowNo, int colNo);	// 设置初始值

private slots:
    void on_btnSetText_clicked();

private:
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);

    Ui::QWDialogLocate *ui;
};

#endif // QWDIALOGLOCATE_H
