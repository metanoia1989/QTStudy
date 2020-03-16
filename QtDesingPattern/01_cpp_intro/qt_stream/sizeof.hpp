#pragma once
#include <QString>
#include <QTextStream>
#include <QChar>
#include <QDate>

void sizeofPrint()
{
    QTextStream cout(stdout);
    char array1[34] = "This is a dreaded C array of char";
    char array2[] = "if not for main, we could avoid it entirely.";
    char* charp = array1;
    int i = 4;
    QString qstring = "This is a unicode QString. Much preferred.";
    Q_ASSERT(sizeof(i) == sizeof(int));
    cout << " c type sizes: \n";
    cout << "sizeof(char) = " << sizeof(char) << "\n";
    cout << "sizeof(wchar_t) = " << sizeof(wchar_t) << "\n";
    cout << "sizeof(int) = " << sizeof(int) << "\n";
    cout << "sizeof(long) = " << sizeof(long) << "\n";
    cout << "sizeof(float) = " << sizeof(float) << "\n";
    cout << "sizeof(double) = " << sizeof(double) << "\n";
    cout << "sizeof(double*) = " << sizeof(double*) << "\n";
    cout << "sizeof(array1) = " << sizeof(array1) << "\n";
    cout << "sizeof(array2) = " << sizeof(array2) << "\n";
    cout << "sizeof(char*) = " << sizeof(charp) << "\n";
    cout << " qt type sizes: \n";
    cout << "sizeof(QString) = " << sizeof(QString) << "\n";
    cout << "sizeof(qint32) = " << sizeof(qint32) << "\n";
    cout << "sizeof(qint64) = " << sizeof(qint64) << "\n";
    cout << "sizeof(QChar) = " << sizeof(QChar) << "\n";
    cout << "sizeof(QDate) = " << sizeof(QDate) << "\n";
    cout << "qstring.length() = " << qstring.length() << "\n";
}
