#include <QtTest>
#include <QDate>
#include <QDebug>
#include <limits.h>

// add necessary includes here

class TestAssertEquals : public QObject
{
    Q_OBJECT

public:

private slots:
    void test_case1();

};


void TestAssertEquals::test_case1()
{
    // start id=testbools
    qDebug() << "Testing bools";
    bool boolvalue = true;
    QVERIFY(1);
    QVERIFY(true);
    QVERIFY(boolvalue);
    qDebug() << QString("We are in file: %1 Line: %2")
                    .arg(__FILE__).arg(__LINE__);
    QCOMPARE(boolvalue, true);
    // end

    // start id=testQStrings
    qDebug() << "Testing QStrings";
    QString string1 = "apples";
    QString string2 = "oranges";
    QString string3 = "apples";
    QCOMPARE(string1, QString("apples"));
    QCOMPARE(QString("oranges"), string2);
    QCOMPARE(string1, string3);
    QVERIFY(string2 != string3);
    // end

    // start id=testQDates
    qDebug() << "Testing QDates";
    QString datestr("2010-11-21");
    QDate dateObj = QDate::fromString(datestr, Qt::ISODate);
    QVERIFY(dateObj.isValid());
    QVariant variant(dateObj);
    QString message(QString("comparing datestr: %1 dateobj: %2 variant: %3")
        .arg(datestr).arg(dateObj.toString()).arg(variant.toString()));
    qDebug() << message;
    QCOMPARE(variant, QVariant(dateObj));
    QCOMPARE(QVariant(dateObj), variant);
    QCOMPARE(variant.toString(), datestr);
    QCOMPARE(datestr, variant.toString());
    QEXPECT_FAIL("", "Keep going!", Continue);
    QCOMPARE(datestr, dateObj.toString());
    // end

    // start id=testnums
    qDebug() << "Testing ints and doubles";
    int i = 4;
    QCOMPARE(4, i);

    uint u (LONG_MAX + 1), v (u / 2);
    QCOMPARE(u, v * 2);

    double d (2. / 3.), e (d / 2);
    QVERIFY(d != e);
    QVERIFY(d == e*2);

    double f(1. / 3.);
    QEXPECT_FAIL("", "Keep going!", Continue);
    QVERIFY(f * 3 == 2);
    // end

    // start id = pointers
    qDebug() << "Teting pointers";
    void *nullpointer = 0;
    void *nonnullpointer = &d;
    QVERIFY(nullpointer != 0);
    qDebug() << "Three is one more item left in the test.";
    QVERIFY(nonnullpointer != 0);
    // end
}

QTEST_APPLESS_MAIN(TestAssertEquals)

#include "tst_testassertequals.moc"
