#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QClipboard>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void clipboardChanged(QClipboard::Mode);

protected:
    void changeEvent(QEvent *e) override;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
