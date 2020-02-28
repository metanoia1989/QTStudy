#include <QCoreApplication>
#include <QTimer>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTimer::singleShot(1000, []() {
        qDebug() << "hello world";
    });

    return a.exec();
}
