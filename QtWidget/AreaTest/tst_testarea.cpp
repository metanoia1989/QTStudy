#include <QtTest>
#include <QString>
#include "area.h"

// add necessary includes here

class TestArea : public QObject
{
    Q_OBJECT

public:
    TestArea();
    ~TestArea();

private slots:
    void test_case1();

};

TestArea::TestArea()
{

}

TestArea::~TestArea()
{

}

void TestArea::test_case1()
{
    Area area(1);
    QVERIFY(qAbs(area.CountArea()-3.14)<0.0000001);	// 检测表达式是否为真
    QVERIFY2(true, "Failure");	// 条件失败时输出信息
}

QTEST_APPLESS_MAIN(TestArea)	// 初始化QApplication对象和测试类，按照测试函数的运行顺序执行所有的测试

#include "tst_testarea.moc"
