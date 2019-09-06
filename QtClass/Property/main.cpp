#include "widget.h"
#include <QApplication>
#include <QtDebug>
#include <QMetaClassInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    /* 类的动态属性 */
    // 如果动态属性不存在，QVariant 对象的 isValid() 函数返回 false, 变量不可用
    qDebug() << w.property("myValue").isValid();

    // 添加属性 myValue
    w.setProperty("myValue", 2.3456);
    // 获取并打印
    qDebug() << w.property("myValue").toDouble();


    // 添加属性 myName
    w.setProperty("myName", "Wid");
    // 获取并打印
    qDebug() << w.property("myName").toString();

    // 获取所有动态属性名称，打印名称列表
    qDebug() << w.dynamicPropertyNames();

    /* 类的附加信息 */
//    // 获取类的附加信息
//    const QMetaObject *pMo = w.metaObject();
//    // 附加信息个数
//    int nInfoCount = pMo->classInfoCount();
//    // 打印所有附加信息
//    for (int i=0;i<nInfoCount;i++) {
//        auto info = pMo->classInfo(i);
//        qDebug() << info.name() << "\t" << info.value();
//    }

//    // 基本信息
//    qDebug() << "Class Name" << pMo->className();
//    qDebug() << "Object Name" << w.objectName();

//    // 判断是否为基类
//    qDebug() << w.inherits("QWidget");
//    qDebug() << w.inherits("nothing");

    w.show();

    return a.exec();
}
