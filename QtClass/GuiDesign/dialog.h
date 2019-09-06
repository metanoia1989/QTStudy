#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_chkBoxUnder_clicked(bool checked);
    void on_chkBoxItalic_clicked(bool checked);
    void on_chkBoxBold_clicked(bool checked);
    void setTextFontColor();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
