#include <QCoreApplication>
#include <QWaitCondition>
#include <QMutex>
#include <QThread>
#include <cstdio>

const int DataSize = 1000;
const int BufferSize = 80;
int buffer[BufferSize];	// 生产者向buffer中写入数据，直到到达终点，然后从起点开始覆盖已经存在的数据
QWaitCondition bufferEmpty;
QWaitCondition bufferFull;
QMutex mutex;	// 使用互斥量保证对线程操作的原子性
int numUsedBytes = 0;	// 变量 numUsedBytes 表示存在多少可用字节
int rIndex = 0;		// 启动两个消费者线程，读取同一个缓冲区，使用 rIndex 指示当前所读取的缓冲的位置，防止重复读取

// 生产者线程
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
        mutex.lock();	// for循环中的所有语句都需要使用互斥量加以保护，以保证其操作的原子性
        if (numUsedBytes==BufferSize) {	// 检测缓冲区是否已被填满
            bufferEmpty.wait(&mutex);	// 如果缓冲已被填满，则等待 缓冲区有空位 bufferEmpyt 条件成立
        }
        buffer[i%BufferSize] = numUsedBytes;	// 如果缓冲区为填满，则向缓冲区写入一整个数值
        ++numUsedBytes;
        bufferFull.wakeAll(); // 唤醒 等待 缓冲区有可用数据 bufferEmpty 条件为真的线程
        mutex.unlock();
    }
}

// 消费者线程
class Consumer : public QThread
{
public:
    Consumer();
    void run();
};
Consumer::Consumer(){}
void Consumer::run()
{
    forever {
        mutex.lock();
        if (numUsedBytes == 0) {	// 缓冲区无数据时，等待 缓冲区有可用数据 bufferFull 条件成立
            bufferFull.wait(&mutex);
        }
        printf("%ul::[%d]=%d\n", currentThreadId(), rIndex, buffer[rIndex]);
        rIndex = (++rIndex)%BufferSize;	// 将 rIndex 变量循环加1
        --numUsedBytes;
        bufferEmpty.wakeAll();	// 唤醒等待 缓冲区有空位bufferEmpty 条件的生产者线程
        mutex.unlock();
    }
    printf("\n");
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Producer producer;
    Consumer consumerA;
    Consumer consumerB;
    producer.start();
    consumerA.start();
    consumerB.start();
    producer.wait();
    consumerA.wait();
    consumerB.wait();

    return a.exec();
}
