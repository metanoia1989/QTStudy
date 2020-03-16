#include <QCoreApplication>
#include <QRegularExpression>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //******************************
    // Introduction
    //******************************
    QRegularExpression re("a pattern");
    QRegularExpression re2;
    re2.setPattern("another pattern");

    // 转义所有反斜杠
    QRegularExpression re3("\\d\\d \\w+");
    // 匹配反斜杠
    QRegularExpression re4("\\\\");
    // 使用Raw字符串
    QRegularExpression re5(R"(\d\d \w+)");

    // 获取当前pattern
    QRegularExpression re6("a third pattern");
    QString pattern = re6.pattern();
    qDebug() <<  "pattern() == \"a third pattern\""<< (pattern == "a third pattern");

    //******************************
    // Pattern Options
    //******************************
    // matches "Qt rocks", but also "QT rocks", "QT ROCKS", "qT rOcKs", etc.
    QRegularExpression re7("Qt rocks", QRegularExpression::CaseInsensitiveOption);

    // re匹配主题字符串中仅包含数字(但至少包含一个)的任何一行
    QRegularExpression re8("^\\d+$");
    re8.setPatternOptions(QRegularExpression::MultilineOption);

    //  get the pattern options currently set
    auto patternOptions = QRegularExpression::MultilineOption|
                            QRegularExpression::DotMatchesEverythingOption;
    QRegularExpression re9("&two.*words$", patternOptions);
    QRegularExpression::PatternOptions options = re9.patternOptions();
    qDebug() << "patternOptions() == construction settings: " << (patternOptions == options);

    //******************************
    // Match Type and Match Options
    //******************************
    /* Normal Matching */
    QRegularExpression re10("\\d\\d \\w+");
    QRegularExpressionMatch match = re10.match("abc123 def");
    bool hasMatch = match.hasMatch();
    qDebug() << R"(\d\d \w+ match 'abc123 def')" << hasMatch;

    //extracting catured substrings
    QRegularExpression re11("\\d\\d \\w+");
    QRegularExpressionMatch match02 = re11.match("abc123 def");
    if (match02.hasMatch()) {
        QString matched = match02.captured(0); // matched == "23 def"
        qDebug() << "extracting captured string: " << matched;
    }

    QRegularExpression re12("\\d\\d \\w+");
    QRegularExpressionMatch match03 = re12.match("12 abc 45 def", 1);
    if (match02.hasMatch()) {
        QString matched = match03.captured(0); // matched == "45 def"
        qDebug() << "extracting offset captured string: " << matched;
    }

    QRegularExpression re13(R"(^(\d\d)/(\d\d)/(\d\d\d\d)$)");
    QRegularExpressionMatch match04 = re13.match("08/12/1985");
    if (match04.hasMatch()) {
        QString day = match04.captured(1);
        QString month = match04.captured(2);
        QString year = match04.captured(3);
        qDebug() << QString("match day month year: %1-%2-%3")
                        .arg(day).arg(month).arg(year);
    }

    // retrieve the starting and the ending offsets
    QRegularExpression re14(R"(abc(\d+)def)");
    QRegularExpressionMatch match05 = re14.match("XYZabc123defXYZ");
    if (match05.hasMatch()) {
        int startOffset = match05.capturedStart(1);
        int endOffset = match05.capturedEnd(1);
        qDebug() << QString("match startOffset %1 endOffset %2")
                        .arg(startOffset).arg(endOffset);
    }

    // extract named captured substrings
    QRegularExpression re15(R"(^(?<date>\d\d)/(?<month>\d\d)/(?<year>\d\d\d\d)$)");
    QRegularExpressionMatch match06 = re15.match("08/12/1985");
    if (match.hasMatch()) {
        QString date = match06.captured("date");
        QString month = match06.captured("month");
        QString year = match06.captured("year");
        qDebug() << QString("extract named captured substring: %1-%2-%3")
                        .arg(date).arg(month).arg(year);
    }

    /* Global Matching */
    QRegularExpression re16("(\\w+)");
    QRegularExpressionMatchIterator i = re16.globalMatch("the quick fox");
    QStringList words;
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString word = match.captured(1);
        words << word;
    }
    qDebug() << "global match" << words;

    /* Partial Matching */
    QString reg(R"(^(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec) \d\d?, \d\d\d\d$)");
    QRegularExpression re17(reg);
    QString input("Jan 21,");
    QRegularExpressionMatch match07 = re17.match(input, 0, QRegularExpression::PartialPreferCompleteMatch);
    bool hasMatch01 = match07.hasMatch();
    bool hasPartialMatch = match07.hasPartialMatch();
    qDebug() << QString("partial matching month hasMatch: %1, hasPartialMatch: %2 ")
                    .arg(hasMatch01).arg(hasPartialMatch) << match07.captured(0);

    /* Incremental/multi-segment matching */
    QRegularExpression re18("(abc)*");
    QRegularExpressionMatch match08 = re18.match("abc", 0, QRegularExpression::PartialPreferFirstMatch);
    bool hasMatch02 = match08.hasMatch();
    bool hasPartialMatch02 = match08.hasPartialMatch();
    qDebug() << QString("Incremental/multi-segment matching: %1, hasPartialMatch: %2 ")
                    .arg(hasMatch02).arg(hasPartialMatch02) << match08.captured(0);

    //******************************
    // Error Handling
    //******************************
    QRegularExpression invalidRe("(unmatched|parenthesis");
    if (!invalidRe.isValid()) {
        QString errorString = invalidRe.errorString();
        int erroOffset = invalidRe.patternErrorOffset();
        qDebug() << QString("regex pattern error on %1 : %2").arg(erroOffset).arg(errorString);
    }

    //******************************
    // Backreference
    //******************************
    qDebug() << "测试反向引用\n";
    QRegularExpression reback(R"(^(?<txt>一个).*(\k<txt>)$)");
    QString str = "一个 ##sdfsdf ： 一个";
    QRegularExpressionMatch matchT = reback.match(str);
    if (matchT.hasMatch()) {
        QString txt = matchT.captured("txt");
        qDebug() << "反向引用所有匹配：" << matchT.captured(0) <<
            matchT.captured(1) << matchT.captured(2);
    }

    return a.exec();
}
