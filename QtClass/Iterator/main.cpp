#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<QString> list;
    list << "A" << "B" << "C" << "D";
    QList<QString>::const_iterator i;
    for (i=list.constBegin(); i!=list.constEnd(); ++i) {
        qDebug() << *i;
    }

    QList<QString>::reverse_iterator ri;
    for (ri=list.rbegin(); ri!=list.rend(); ++ri) {
        *ri = ri->toLower();
        qDebug() << *ri;
    }

    QMap<int, int> map;
    map.insert(1, 10);
    map.insert(2, 20);
    map.insert(3, 30);
    map.insert(4, 40);
    QMap<int, int>::const_iterator mi;
    for (mi=map.constBegin();mi!=map.constEnd();++mi) {
        qDebug() << mi.key() << ":" << mi.value();
    }

    return a.exec();
}
