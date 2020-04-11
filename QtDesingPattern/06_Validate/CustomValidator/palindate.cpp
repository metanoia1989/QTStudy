#include "palindate.h"

Palindate::Palindate(QObject *parent) : QValidator(parent)
{
}

QValidator::State Palindate::validate(QString &input, int &pos) const
{
    QString inpStr(input.toLower());
    QString skipchars("-_!,;.\t");
    for (QChar ch : skipchars) {
        inpStr = inpStr.remove(ch);
    }
    QString revStr;
    for (int i = inpStr.length(); i > 0; --i)
        revStr.append(inpStr[i - 1]);
    if (inpStr == revStr) {
        return Acceptable;
    } else {
        return Intermediate;
    }
}
