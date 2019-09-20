#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QFile data("data.txt");
    if (data.open(QFile::WriteOnly|QFile::Truncate)) {	// 将原来的文件清空，输出时格式设为左对齐
        QTextStream out(&data);
        out << QObject::tr("score: ") << qSetFieldWidth(10) << left << 90 << endl;
    }

    return a.exec();
}
