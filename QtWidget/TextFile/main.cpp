#include <QCoreApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QFile file("textFile1.txt");
    if (file.open(QIODevice::ReadOnly)) {
        char buffer[2048];
        qint64 lineLen = file.readLine(buffer, sizeof(buffer)); // 读取文本一行
        if (lineLen != -1) {
            qDebug() << buffer;
        }
    }

    return a.exec();
}
