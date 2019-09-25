#include <QtTest>

// add necessary includes here
#include <QString>

class TestQString : public QObject
{
    Q_OBJECT

public:
    TestQString();
    ~TestQString();

private slots:
    // 每个 private slot 都是一个被QTest::qExec()自动调用的测试函数
    void testToLower();	// 测试字符串转换为全小写字符
    void testToLower_data(); // 提供测试数据，测试函数名加上后缀 _data() 即可

};

TestQString::TestQString()
{

}

TestQString::~TestQString()
{

}

void TestQString::testToLower()
{
    // 获取测试数据
    QFETCH(QString, string);
    QFETCH(QString, result);
    // 如果两个参数不同，则其值会分别显示出来
    QCOMPARE(string.toLower(), result);	// 用等号比较两个值
    QVERIFY2(true, "Failture");
}

void TestQString::testToLower_data()
{
    // 添加测试列
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");
    // 添加测试数据
    QTest::newRow("lower") << "hello" << "hello";
    QTest::newRow("mixed") << "heLLo" << "hello";
    QTest::newRow("upper") << "HELLO" << "HELLO";
}


// 生成能够独立运行的测试代码
QTEST_APPLESS_MAIN(TestQString)

#include "tst_testqstring.moc"
