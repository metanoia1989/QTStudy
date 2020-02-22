#include <QCoreApplication>
#include <QString>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QString message("Hello World!");
    QFile file(QDir::home().absoluteFilePath("out.txt"));
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Can not open file with write access";
        return -1;
    }
    QTextStream stream(&file);
    stream << message;
    qDebug() << QDir::home().absoluteFilePath("out.text");
    return 0;
}
