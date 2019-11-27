#include "mainwindow.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QTextCodec>

#include "dialoglogin.h"

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);	// 解决汉字乱码问题

    QApplication a(argc, argv);

    DialogLogin *dlgLogin = new DialogLogin; // 常见 splash 对话框
    if (dlgLogin->exec() == QDialog::Accepted) {
        MainWindow w;
        w.show();
        return a.exec();
    }

    return 0;
}
