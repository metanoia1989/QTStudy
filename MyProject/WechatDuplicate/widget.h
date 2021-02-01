#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void showError(const QString& msg);

private slots:

    void on_pushButton_clicked();

    void on_btn_start_clicked();


    void on_spin_execute_num_valueChanged(int arg1);

private:
    Ui::Widget *ui;

    QSettings settings;
};
#endif // WIDGET_H
