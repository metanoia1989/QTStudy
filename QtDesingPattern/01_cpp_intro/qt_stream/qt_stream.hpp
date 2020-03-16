#pragma once
#include <QTextStream>
#include <QDebug>

QTextStream cin(stdin);
QTextStream cout(stdout);
QTextStream cerr(stderr);

void streamPrint()
{
    int num1{1234}, num2{2345};
    cout << oct << num2 << '\t'
         << hex << num2 << '\t'
         << dec << num2 << endl;
    double dub{1357};
    cout << dub << '\t'
         << forcesign << dub << '\t'
         << forcesign << dub << endl;
    dub = 1234.5678;
    cout << dub << '\t'
         << fixed << dub << '\t'
         << scientific << dub << '\n'
         << noforcesign << dub << endl;
    qDebug() << "Here is a debug message with " << dub << "in it.";
    qDebug("Here is one with the number %d in it.", num1);
}
