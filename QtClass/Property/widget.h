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

    // 类的附加信息
    Q_CLASSINFO("Version", "1.0.0")
    Q_CLASSINFO("Authro", "Adam Smith")
    Q_CLASSINFO("Site", "https://www.metanoia")

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
