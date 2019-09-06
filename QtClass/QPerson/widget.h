#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "qperson.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();


private:
    Ui::Widget *ui;
    QPerson *boy;
    QPerson *girl;

private slots:
    // 自定义槽函数
    void on_ageChanged(int value);
    void on_spin_valueChanged(int arg1);
    // 界面按钮的槽函数
    void on_btnClear_clicked();
    void on_btnBoyInc_clicked();
    void on_btnGirlInc_clicked();
    void on_btnClassInfo_clicked();
};

#endif // WIDGET_H
