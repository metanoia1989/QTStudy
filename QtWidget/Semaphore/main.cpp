#include <QCoreApplication>
#include <QSemaphore>
#include <QThread>
#include <cstdio>

const int DataSize = 1000;
const int BufferSize = 80;
int buffer[BufferSize];	// 生产者向buffer中写入数据，直到到达终点，然后从起点开始覆盖已经存在的数据
QSemaphore freeBytes(BufferSize);	// 信号量控制可被生产者填充的缓冲区部分，被初始化为 BufferSize(80) 表示一开始有BufferSize个缓冲区单元可被填充
QSemaphore usedBytes(0);	// 控制可被消费者读取的缓冲区部分，被初始化为0，表示程序一开始时缓冲区没有数据可供读取

// 生产者类
class Producer : public QThread
{
public:
    Producer();
    void run();
};
Producer::Producer(){}
void Producer::run()
{
    for (int i=0;i<DataSize;i++) {
        // 生产者线程先获取一个空闲单元，如果此时缓冲区被消费者尚未读取的数据填满，
        // 此函数将会阻塞，直到消费者读取了为止
        freeBytes.acquire();
        // 一旦生产者读取了某个空闲单元，就使用当前的缓冲区单元序号填写这个缓冲区单元
        buffer[i%BufferSize]=(i%BufferSize);
        // 调用该函数将可用资源加1，表示消费者此时可以读取这个刚刚填写的单元
        usedBytes.release();
    }
}

// 消费者类
class Consumer : public QThread
{
public:
    Consumer();
    void run();
};
Consumer::Consumer(){};
void Consumer::run()
{
    for (int i=0;i<DataSize;i++) {
        // 消费者线程首先获取一个可被读取的单元，如果缓冲区中没有包含任何可以读取的数据，对此函数的调用就会阻塞，直到生产者生产了一些数据为止
        usedBytes.acquire();
        // 一旦消费者获取了这个单元，会将这个单元的内容打印出来
        fprintf(stderr, "%d", buffer[i%BufferSize]);
        if (i%16==0 && i!=0) {
            fprintf(stderr, "\n");
        }
        // 调用该函数使得这个单元变为空闲，以备生产者下次填充
        freeBytes.release();
    }
    fprintf(stderr, "\n");
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Producer producer;
    Consumer consumer;
    /* 启动生产者和消费者线程 */
    producer.start();
    consumer.start();
    /* 等的生产者和消费者各自执行完毕后自动退出 */
    producer.wait();
    consumer.wait();

    return a.exec();
}

