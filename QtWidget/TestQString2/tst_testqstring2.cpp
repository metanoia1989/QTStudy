#include <QtTest>

// add necessary includes here
#include <QString>

class TestQString2 : public QObject
{
    Q_OBJECT

public:
    TestQString2();
    ~TestQString2();

private slots:
    void testBenchmark();	// 简单性能测试

};

TestQString2::TestQString2()
{

}

TestQString2::~TestQString2()
{

}

void TestQString2::testBenchmark()
{
    QString str("heLLO");
    // 用于性能测试的代码
    QBENCHMARK
    {
        str.toLower();
    }
    QVERIFY2(true, "Failture");
}

QTEST_APPLESS_MAIN(TestQString2)

#include "tst_testqstring2.moc"
