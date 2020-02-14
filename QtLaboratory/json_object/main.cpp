#include <QCoreApplication>
#include <QJsonObject>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QJsonObject obj;
    obj.insert("a", "1");

    QJsonObject obj1;
    obj1.insert("c", "2");
    obj1.insert("d", "4");

//    obj.insert("b", obj1);
    obj["b"] = obj1;

    qDebug() << obj;
    obj1["c"] = "3";
    qDebug() << obj;
    qDebug() << obj1;
    qDebug() << (obj["c"] == obj1);


    return a.exec();
}
