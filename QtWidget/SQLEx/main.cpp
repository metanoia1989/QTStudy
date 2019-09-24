#include "mainwindow.h"
#include <QApplication>
#include <QDialog>
#include "connectdlg.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConnDlg dialog;
    if (dialog.exec() != QDialog::Accepted) {
        return -1;
    }
    dialog.show();

//    MainWindow w;
//    w.show();

    return a.exec();
}
