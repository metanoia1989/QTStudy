#include "mainwindow.h"
#include "share/WizWin32Helper.h"
#include <QApplication>
#include <QStyleFactory>
#include <QDebug>

int main(int argc, char *argv[])
{
    // 仅Windows平台可以使用

    // 暂时先采用UI缩放+字体缩小的方案来适配Windows高分屏
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    // 配置字体
    QFont appFont = WizCreateWindowsUIFont(app);
    QApplication::setFont(appFont);

    // tooltip 样式
    qDebug() << QStyleFactory::keys();
    app.setStyle(QStyleFactory::create("fusion"));
    app.setStyleSheet("QToolTip { \
                     font: 12px; \
                     color:#000000; \
                     padding:0px 1px; \
                     background-color: #F8F8F8; \
                     border:0px;}");

    MainWindow w;
    w.show();
    return app.exec();
}
