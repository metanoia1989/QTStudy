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

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    void myDrawFilledRect();
    void myDrawTextureRect();
    void myDrawGradient();
    void total();
    void myDrawShape();	// 绘制基本图形

    Ui::Widget *ui;
};

#endif // WIDGET_H
