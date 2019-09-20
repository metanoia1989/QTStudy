#include <QCoreApplication>
#include <QFile>
#include <QDataStream>
#include <QDate>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    /* 将二进制数据写到数据流 */
    QFile file("binary.dat");
    file.open(QIODevice::WriteOnly|QIODevice::Truncate);
    QDataStream out(&file);	// 将数据序列化
    out << QString(QObject::tr("周贺军： ")); 	// 字符串序列化
    out << QDate::fromString("1996/09/25", "yyyy/MM/dd");
    out << static_cast<qint32>(23);	// 整数序列化
    file.close();

    /* 从文件中读取数据 */
    file.setFileName("binary.dat");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "error!";
        return -1;
    }
    QDataStream in(&file);
    QString name;
    QDate birthday;
    qint32 age;
    in >> name >> birthday >> age;
    qDebug() << name << birthday << age;
    file.close();


    return a.exec();
}
