#include <iostream>
#include <sstream>
#include <fstream>

int main(int argc, char const *argv[])
{
    using namespace std;
    ostringstream strbuf;

    int lucky = 7;
    float pi = 3.14;
    double e = 2.71;

    cout << "An in-memory stream" << endl;
    strbuf << "luckynumber: " << lucky << endl
        << "pi: " << pi << endl
        << "e: " << pi << endl;

    string strval = strbuf.str(); // 转换 stringstream 为 string
    cout << strval;

    ofstream outf; // 创建输出文件流
    outf.open("mydata");
    outf << strval;
    outf.close();

    // start id="reading"          
    cout << "Read data from the file - watch for errors." << endl;
    string newstr;
    ifstream inf;
    inf.open("mydata");
    if (inf) { // 确认文件存在，然后读取
        int lucky2;
        inf >> newstr >> lucky2;
        if (lucky != lucky2) {
            cerr << "ERROR! wrong " << newstr << lucky2 << endl;
        } else {
            cout << newstr << " OK" << endl;
        }

        float pi2;
        inf >> newstr >> pi2;
        if (pi2 != pi) {
            cerr << "ERROR! Wrong " << newstr << pi2 << endl;
        } else {
            cout << newstr << " OK" << endl;
        }

        double e2;
        inf >> newstr >> e2;
        if (e2 != e) {
            cerr << "ERROR: Wrong " << newstr << e2 << endl;
        } else {
            cout << newstr << " OK" << endl;
        }
        inf.close();
    }
    // end

    // start id="getline"
    cout << "Read from file line-by-line" << endl;
    inf.open("mydata");
    if (inf) {
        while (not inf.eof()) {
            getline(inf, newstr);
            cout << newstr << endl;
        }
        inf.close();
    }

    return 0;
}
