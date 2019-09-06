#include <QCoreApplication>
#include <QtDebug>
#include <QQueue>

void TestJavaIterator();
void TestSTLIterator();
void TestQQueue();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    TestJavaIterator();
//    TestSTLIterator();
    TestQQueue();


    return a.exec();
}

void TestJavaIterator()
{
    /* java 风格迭代器 */
    // 只读迭代器
    QList<int> list;
    list << 1 << 2 << 3 << 4 << 5;
    QListIterator<int> i(list);
    for(;i.hasNext();) {
        qDebug() << i.next();
    }

    // 读写迭代器
    QList<int> list2;
    QMutableListIterator<int> i2(list);
    for (int j=0; j<10; ++j) {
        i2.insert(j);
    }
    for (i2.toFront(); i2.hasNext();) {
        qDebug() << i2.next();
    }
    for (i2.toBack(); i2.hasPrevious(); ) {
        if (i2.previous() %2 == 0) {
            i2.remove();
        } else {
            i2.setValue(i2.peekNext()*10);
        }
    }
    for (i2.toFront();i2.hasNext();) {
        qDebug() << i2.next();
    }

}

void TestSTLIterator()
{
    QList<int> list;
    for(int j=0;j<10;j++)
        list.insert(list.end(), j);
   QList<int>::iterator i; // 初始化一个QList<int>::iterator 读写迭代器
   for(i=list.begin();i!=list.end();++i) {
       qDebug() << (*i);
       *i = (*i) * 10;
   }
   // 初始化一个 QList<int>::const_iterator 读写器
   QList<int>::const_iterator ci;
   for(ci=list.constBegin();ci!=list.constEnd();++ci)
       qDebug() << *ci;
}

void TestQQueue()
{
    QQueue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    while (!queue.isEmpty()) {
        qDebug() << queue.dequeue();
    }

}
