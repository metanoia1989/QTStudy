#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include "qdicethread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

protected:
    void closeEvent(QCloseEvent *) override;

private slots:
    void onthreadA_started();
    void onthreadA_finished();
    void onthreadA_newValue(int seq, int diceValue);

    void on_btnStartThread_clicked();

    void on_btnStopThread_clicked();

    void on_btnClear_clicked();

    void on_btnDiceBegin_clicked();

    void on_btnDiceEnd_clicked();

private:
    Ui::Dialog *ui;
    QDiceThread threadA;
};
#endif // DIALOG_H
