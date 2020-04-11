#include <QTextStream>
#include <QRegExp>
#include <QString>

static QTextStream cout(stdout);
static QTextStream cin(stdin);

QRegExp filtercharacters(R"([\s-\+\(\)\-])");
QRegExp usformat(R"((\+?1[- ]?)?\(?(\d{3})\)?[\s-]?(\d{3})[\s-]?(\d{4}))");
QRegExp genformat(R"((00)?([[3-9]\d{1,2})(\d{2})(\d{7})$)");
QRegExp genformat2(R"((\d\d)(\d\d)(\d{3}))");

QString countryName(QString ccode);
QString stdinReadPhone();

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    QString str;
    do {
        str = stdinReadPhone();
        if (str != "q")
            cout << " validated: " << str << endl;
    } while (str != "q");

    return 0;
}


QString countryName(QString ccode)
{
    if (ccode == "31") return "Netherlands";
    else if (ccode == "351") return "Portugal";
    else if (ccode == "41") return "Switzerland";
    else if (ccode == "420") return "Czech Republic";
    else if (ccode == "56") return "Chile";
    else if (ccode == "595") return "Paraguay";
    else if (ccode == "62") return "Indonesia";
    else if (ccode == "680") return "Palau";
    else if (ccode == "86") return "China";
    else if (ccode == "886") return "Taiwan";
    else if (ccode == "91") return "India";
    else if (ccode == "962") return "Jordan";
    else return "Unknow - but possibly valid";
}

QString stdinReadPhone()
{
    QString str;
    bool knownFormat = false;
    do {
        cout << "Enter a phone number (or q to quit)";
        cout.flush();
        str = cin.readLine();
        if (str == "q") return str;
        str.remove(filtercharacters);
        if (genformat.exactMatch(str)) {
            QString country = genformat.cap(2);
            QString citycode = genformat.cap(3);
            QString rest = genformat.cap(4);
            if (genformat2.exactMatch(rest)) {
                knownFormat = true;
                QString number = QString("%1-%2-%3")
                    .arg(genformat2.cap(1))
                    .arg(genformat2.cap(2))
                                     .arg(genformat2.cap(3));
                str = QString("(%1) + %2 (0)%3-%4").arg(countryName(country))
                          .arg(country).arg(citycode).arg(number);
            }
        } else if (usformat.exactMatch(str)) {
            knownFormat = true;
            QString areacode = usformat.cap(2);
            QString exchange = usformat.cap(3);
            QString number = usformat.cap(4);
            str = QString("(US/Canda) +1 %1-%2-%3")
                      .arg(areacode).arg(exchange).arg(number);
        }

        if (not knownFormat)
            cout << "Unknown format" << endl;
    } while (not knownFormat);
    return str;
}

