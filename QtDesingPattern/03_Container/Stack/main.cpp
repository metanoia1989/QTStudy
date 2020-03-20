#include <QString>
#include <QDebug>
#include "stack.h"

int main(int argc, char *argv[])
{
    Stack<int> intstack1, intstack2;
    for (int i = 0; i < 4; ++i) {
        intstack1.push(i);
        intstack2.push(i * 2);
    }
    while (intstack1.count()) {
        int value = intstack1.pop();
        qDebug() << value;
    }

    Stack<QString> stringStack;
    stringStack.push("First on");
    stringStack.push("Second on");
    stringStack.push("First off");
    QString value;
    while (stringStack.count()) {
        value = stringStack.pop();
        qDebug() << value;
    }
    qDebug() << "Now intstack2 will self destruct.";

    return 0;
}
