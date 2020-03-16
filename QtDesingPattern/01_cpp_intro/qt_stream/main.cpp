#include <QCoreApplication>
#include <QTextStream>
#include "qt_stream.hpp"
#include "sizeof.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QTextStream cout(stdout);
    QStringList argList = app.arguments();
    cout << "argc = " << argc << endl;
    for (int i = 0; i < argList.length(); ++i){
        cout << QString("argv#%1 is %2").arg(i).arg(argList.at(i)) << endl;
    }
    int num = argList.at(argc - 1).toInt();
    cout << num * 2 << endl;

    streamPrint();
    sizeofPrint();
}
