#include "mainwindow.h"
#include <QTextEdit>
#include "windows.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Splash Example"));
    QTextEdit *edit = new QTextEdit;
    edit->setText("Spash Example");
    setCentralWidget(edit);
    resize(600, 450);
    Sleep(1000);
}

MainWindow::~MainWindow()
{

}
