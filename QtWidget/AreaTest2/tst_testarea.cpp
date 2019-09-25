#include <QtTest>

// add necessary includes here
#include <QString>
#include "area.h"

class TestArea : public QObject
{
    Q_OBJECT

public:
    TestArea();
    ~TestArea();

private slots:
    void testCountArea();	// 测试函数
    void testCountArea_data();	// 测试函数数据


};

TestArea::TestArea()
{

}

TestArea::~TestArea()
{

}

void TestArea::testCountArea()
{
    // 获取测试数据
    QFETCH(Area, area);
    QFETCH(double, r);
    QVERIFY(qAbs(area.CountArea()-r)<0.0000001);
    QVERIFY2(true, "Failture");
}

void TestArea::testCountArea_data()
{
    // 定义测试数据列
    QTest::addColumn<Area>("area");
    QTest::addColumn<double>("r");

    // 建立测试数据
    QTest::newRow("1") << Area(1) << 3.14;
    QTest::newRow("2") << Area(2) << 12.56;
    QTest::newRow("3") << Area(3) << 28.26;
}

QTEST_APPLESS_MAIN(TestArea)

#include "tst_testarea.moc"
