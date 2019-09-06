#include <QCoreApplication>
#include <QtDebug>

void Test_setNum();
void Test_arg();
void Test_substring();
void Test_Str();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /* Qt 内存分配策略 */
    QString str;
    for (int i=0; i<9000; ++i)
        str.append("a");
//    qDebug()<<str;

    /* 操作字符串 */
    // 字符串相加操作
    QString str1 = "Welcome ";
    str1 = str1 + "to you!";
    QString str2 = "Hello, ";
    str2 += "Worldl!";
//    qDebug() << str1 << str2;

    // QString::append() 实现字符串相加操作
    QString str3 = "Welcome ";
    QString str4 = "to ";
    str3.append(str4);
    str3.append("you!");
//    qDebug() << str3;

    // 使用QString::sprintf() 进行格式化输出
    QString str5;
    str5.sprintf("%s", "Welcome ");
//    qDebug() << str5;
    str5.sprintf("%s", " to you!");
//    qDebug() << str5;
    str5.sprintf("%s %s", "Welcome ", "to you!");
//    qDebug() << str5;

    // 使用 QString::arg() 串联组合字符串
    QString str6;
    str6 = QString("%1 was born in %2.").arg("John").arg("1998");
//    qDebug() << str6;

    // QString::trimmed() QString::simplified() 删除空白字符
    QString str7 = " Welcome \t to \n you!	";
//    qDebug() << str7.trimmed();
//    qDebug() << str7.simplified();

    /* 查询字符串 */
    QString str8 = "Welcome to you!";
//    qDebug() << "startsWith" << str8.startsWith("Welcome", Qt::CaseSensitive); // 大小写敏感
//    qDebug() << "startsWith" << str8.startsWith("welcome", Qt::CaseSensitive); // 大小写敏感
//    qDebug() << "startsWith" << str8.startsWith("welcome", Qt::CaseInsensitive); // 大小写不敏感
//    qDebug() << "endsWith" << str8.endsWith("u!", Qt::CaseSensitive); // 大小写敏感
//    qDebug() << "endsWith" << str8.endsWith("U!", Qt::CaseSensitive); // 大小写敏感
//    qDebug() << "contains" << str8.contains("to", Qt::CaseSensitive); // 大小写敏感

    /* 字符串转换 */
    QString str9 = "125";
    bool ok;
    int hex = str9.toInt(&ok, 16);
    int dec = str9.toInt(&ok, 10);
//    qDebug() << "str9 转16进制数及10进制数" << hex << dec;

    QString str10 = "Welcome to you!";
    QByteArray ba = str10.toLatin1();
//    qDebug() << ba;
//    ba.append("Hello, World");
//    qDebug() << ba.data();

    /* NULL 字符串与空字符串 */
//    qDebug() << QString().isNull(); // true
//    qDebug() << QString().isEmpty(); // true
//    qDebug() << QString("").isNull(); // false
//    qDebug() << QString("").isEmpty(); // true

//    Test_setNum();
//    Test_arg();
//    Test_substring();
//    Test_Str();
    QHash<QString, QList<double>> t;
    qDebug("测试输出，原来这个方便");

    return a.exec();
}

/* 测试基本数值类型转换为QString的setNum操作 */
void Test_setNum()
{
    QString strTest;
    // to Hex string
    short numHex = 127;
    strTest.setNum(numHex, 16);
    qDebug() << "Hex: " << strTest;

    // to Oct string
    int numOct = 63;
    strTest.setNum(numOct, 8);
    qDebug() << "Oct: " << strTest;

    // to normal Dec string
    int numDec = 800;
    strTest.setNum(numDec);
    qDebug() << "Normal: " << strTest;

    // to float string
    double numFixed = 123.78999;
    strTest.setNum(numFixed, 'f', 3);
    qDebug() << "Fixed: " << strTest;

    // to scientific double string
    double numScientific = 456.78999;
    strTest.setNum(numScientific, 'e', 6);
    qDebug() << "Scientific: " << strTest;
}



/* 测试字符串格式化 arg 函数 */
void Test_arg()
{
     // 使用 strResult 存储 arg 返回的新对象
    QString strResult;

    // Dec
    long numDec = 800;
    QString strMod = QObject::tr("Normal: %1");
    strResult = strMod.arg(numDec);	// %1 是占位符，是第一个arg函数参数变量转后的字符串填充到%1位置
    qDebug() << "Mod: " << strMod << " \t Result: " << strResult;

    // Oct
    int numOct = 63;
    strResult = QObject::tr("Oct: %1").arg(numOct, 4, 8, QChar('0'));	// numOct 转换后为4字符宽，8进制，填充0
    qDebug() << strResult;

    // Hex
    short numHex = 127;
    QString strPrefix = QObject::tr("0x");
    // 占位符里可填充数值转的字符串，也可以直接填充原有的字符串
    strResult = QObject::tr("Hex: %1%2").arg(strPrefix).arg(numHex, 0, 16);	// 串联：第一个arg函数填充到%1，第二个arg参数填充到 %2
    qDebug() << strResult;

    // double
    double numReal = 123.78999;
    strResult = QObject::tr("Fixed: %1 \t Scientific: %2").arg(numReal, 0, 'f').arg(numReal, 0, 'e', 3);
    qDebug() << strResult;

    // 占位符可重复，也可乱序
    int one = 1, two = 2, three = 3;
    strResult = QObject::tr("%1 小于 %2，%1 小于 %3，%3 小于 %2").arg(one).arg(two).arg(three);
    qDebug() << strResult;
}

/* 操作字符串 */
void Test_substring()
{
    QString strOne = QObject::tr("abcd");
    QString strThree = strOne.repeated(3);	// abcd 重复三次
    qDebug() << strThree.isEmpty();
    qDebug() << strThree.length() << "\t" << strThree.size();	// 都是长度
    qDebug() << strThree;

    // 子串查询
    qDebug() << strThree.contains(strOne); // 是否包含
    qDebug() << strThree.count(strOne); // 包含几个
    qDebug() << strThree.startsWith(strOne); // 打头的子串
    qDebug() << strThree.indexOf(strOne); // 左边开始的子串位置
    qDebug() << strThree.lastIndexOf(strOne); // 右边开始的子串位置

    // 剔除两端的空白
    QString strComplexFileName = QObject::tr(" 	/home/user/somefile.txt  \t\t ");
    QString strFileName = strComplexFileName.trimmed();
    qDebug() << strFileName;
    if(strFileName.endsWith(QObject::tr(".txt")))
    {
        qDebug() << "This is a .txt file";
    }

    // 分隔子串
    QStringList subsList = strFileName.split(QChar('/'));
    for (int i=0; i<subsList.length(); i++) // 打印各个子串
    {
        qDebug() << i << "\t" << subsList[i];
    }

    // 获取段落
    QString subsections = strFileName.section(QChar('/'), 2, 3);
    qDebug() << subsections;
}

/* QByteArray 当做 QString 的使用示例 */
void Test_Str() //内码 UTF-8
{

   //数值与字符串转换
   int nDec = 800;
   QByteArray basDec;
   basDec.setNum(nDec);    //数值转字符串
   qDebug()<<basDec;
   QByteArray basReal = "125.78999";
   double dblReal = basReal.toDouble();    //字符串转数值
   qDebug()<<fixed<<dblReal;


   //运算符
   QByteArray basABCD = "ABCD";
   QByteArray basXYZ = "XYZ";
   qDebug()<<(basABCD < basXYZ);   //二者字符编码一致才能比较！
   qDebug()<<(basABCD == basXYZ);
   qDebug()<<(basABCD >= basXYZ);
   qDebug()<<(basABCD + basXYZ);

   //子串处理
   QByteArray basHanzi = "1234打印汉字";
   //作为字符串时 QByteArray::length() 和 qstrlen() 一致
   qDebug()<<basHanzi.length()<<"\t"<<qstrlen( basHanzi.data() );

   //重复
   QByteArray basMoreHanzi = basHanzi.repeated(2);
   qDebug()<<basMoreHanzi.count("1234"); //统计次数
   qDebug()<<basMoreHanzi.startsWith("1234");  //开头判断
   qDebug()<<basMoreHanzi.endsWith("汉字");     //结尾判断
   qDebug()<<basMoreHanzi.indexOf("1234");   //从左边查出现位置
   qDebug()<<basMoreHanzi.lastIndexOf("1234"); //从右边查出现位置

   //替换
   basMoreHanzi.replace("1234", "一二三四");
   qDebug()<<basMoreHanzi;


   //切割字符串
   QByteArray basComplexFile = "   /home/user/somefile.txt  \t\t ";
   QByteArray basFileName = basComplexFile.trimmed();  //剔除两端空白
   qDebug()<<basFileName;
   //分隔得到新的 QByteArray 对象列表
   QList<QByteArray> baList = basFileName.split('/');
   //打印
   for(int i=0; i<baList.length(); i++)
   {
       qDebug()<<i<<"\t"<<baList[i];
   }
}
