#include <QCoreApplication>
#include <QDebug>

void QMapJavaStyleUse();
void QMapSTLStyleUse();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    QMapJavaStyleUse();
    QMapSTLStyleUse();

    return a.exec();
}

void QMapJavaStyleUse()
{
    QMap<QString, QString> map;
    // 插入<城市, 区号>
    map.insert("beijing", "111");
    map.insert("shagnhai", "021");
    map.insert("nanjing", "025");
    QMapIterator<QString, QString> i(map);
    for(;i.hasNext();) {
        i.next();
        qDebug() << " " << i.key() << " " << i.value();
    }
    QMutableMapIterator<QString, QString> mi(map);
    if(mi.findNext("111")) {
        mi.setValue("010");
    }
    QMapIterator<QString, QString> modi(map);
    qDebug() << " ";
    for(;modi.hasNext();) {
        modi.next();
        qDebug() << " " << modi.key() << " " << modi.value();
    }
}

void QMapSTLStyleUse()
{
    QMap<QString, QString> map;
    // 插入<城市, 区号>
    map.insert("beijing", "111");
    map.insert("shagnhai", "021");
    map.insert("nanjing", "025");
    QMap<QString, QString>::const_iterator i;
    for(i=map.constBegin();i!=map.constEnd();++i) {
        qDebug() << " " << i.key() << " " << i.value();
    }
    QMap<QString, QString>::iterator mi;
    mi = map.find("beijing");
    if (mi!=map.end()) {
        qDebug() << "找到要查找的值了: " << mi.value();
        mi.value() = "010";
    }


    QMap<QString, QString>::const_iterator modi;
    qDebug() << " ";
    for(modi=map.constBegin();modi!=map.constEnd();++modi)
        qDebug() << " " << modi.key() << " " << modi.value();

}
