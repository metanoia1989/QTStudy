#include <QtGui>

QString name()
{
    return QString("Alan");
}

typedef QString (*funcPtr)(); // 定义函数指针
Q_DECLARE_METATYPE(funcPtr); // 注册元类型，用于QVariant

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    qRegisterMetaType<funcPtr>("funcPtr"); // 注册器，可以用于队列的信号
    funcPtr ptr = name;

    QString v = (*ptr)();
    qDebug() << v << endl;
}
