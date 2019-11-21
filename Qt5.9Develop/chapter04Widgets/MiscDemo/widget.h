#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_SliderRed_valueChanged(int value);

    void on_dial_valueChanged(int value);

    void on_radioBtnDec_clicked();

    void on_radioBtnBin_clicked();

    void on_radioBtnHex_clicked();

    void on_radioBtnOct_clicked();

    void on_SliderV_valueChanged(int value);

    void on_SliderH_valueChanged(int value);

    void on_ScrollBarV_sliderMoved(int position);

    void on_ScrollBarH_sliderMoved(int position);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
