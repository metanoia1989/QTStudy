#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
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

    void onthreadB_started();
    void onthreadB_finished();
    void onthreadB_newValue(int *data, int count, int bufNo);

    void on_btnStartThread_clicked();
    void on_btnStopThread_clicked();
    void on_btnClear_clicked();

private:
    Ui::Dialog *ui;
    QThreadDAQ threadProducer;
    QThreadShow threadConsumer;
};
#endif // DIALOG_H
