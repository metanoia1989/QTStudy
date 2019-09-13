#include "mainwindow.h"
#include <QApplication>
#include <QSplitter>
#include <QTextEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font("ZYSong18030", 12); // 指定显示字体
    a.setFont(font);

    // 主分割窗口
    QSplitter *splitterMain = new QSplitter(Qt::Horizontal, nullptr); // 水平分割主窗口
    QTextEdit *textLeft = new QTextEdit(QObject::tr("Left Widget"), splitterMain);
    textLeft->setAlignment(Qt::AlignCenter); // 文本编辑框中文字的对齐方式

    // 右分割窗口
    QSplitter *splitterRight = new QSplitter(Qt::Vertical, splitterMain); // 垂直分割，以主分割窗口为父窗口
    splitterRight->setOpaqueResize(false); // 设定分割窗口的分隔条在拖拽时是否为实时更新显示
    QTextEdit *textUp = new QTextEdit(QObject::tr("Top Widget"), splitterRight);
    textUp->setAlignment(Qt::AlignCenter);
    QTextEdit *textBottom = new QTextEdit(QObject::tr("Bottom Widget"), splitterRight);
    textBottom->setAlignment(Qt::AlignCenter);

    splitterMain->setStretchFactor(1, 1); // 设置可伸缩控件
    splitterMain->setWindowTitle(QObject::tr("Splitter"));
    splitterMain->show();

//    MainWindow w;
//    w.show();

    return a.exec();
}
