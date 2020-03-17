# 学习教程为先
- [PyQt5-Chinese-tutorial](https://maicss.gitbooks.io/pyqt5/content/)
- [PyQt5系列教程（1）：我与PyQt5有个约会](https://zhuanlan.zhihu.com/p/28012981)
- [python gui PyQT5](https://pythonspot.com/pyqt5/)
- [PyQt 同上的](https://pythonprogramminglanguage.com/pyqt/)
- [Tutorial for creating Python/Qt GUIs with fbs](https://github.com/mherrmann/fbs-tutorial) 简化打包
- [PyQt5 tutorial – Python GUI programming examples](https://likegeeks.com/pyqt5-tutorial/) 使用 QT Design 设计页面
- [PyQt5 tutorial](http://zetcode.com/gui/pyqt5/) 经典教程
- [Graphical user interface design with Python & Qt](http://sig9.ecanews.org/pdfs-rovinj/Graphical_user_interface-karine.sparta.pdf) 一些超级棒的设计案例
- [GUI Programming with PyQt—By Example](http://heim.ifi.uio.no/trentonw/inf3330/doc/pyqt-doc.pdf)
- [pyqt5 example](https://github.com/baoboa/pyqt5/tree/master/examples)
- [PyQt5 代码片段集合](https://vra.github.io/2018/01/13/pyqt5-code-snippets/)
- [PyQt5应用与实践](http://www.cnblogs.com/skynet/p/4229556.html)
- [A simple GUI for rtl_433 with Python and Qt](https://raspberrypiandstuff.wordpress.com/2017/07/31/a-simple-gui-for-rtl_433-with-python-and-qt/)
- [plotpy](https://pythonhosted.org/plotpy/index.html)
- [PyQt5-Apps](https://github.com/LewisTian/PyQt5-Apps)
- [有哪些颜值高的 PyQt/Qt 应用？](https://www.zhihu.com/question/39607624)
- [PyQt5图形界面编程 - 知乎专栏](https://zhuanlan.zhihu.com/xdbcb8)
- [如虎添翼！在PyQt5中便捷的进行数据库操作！](https://mp.weixin.qq.com/s?__biz=MzI5NDY1MjQzNA==&mid=2247488097&idx=1&sn=543593cb9f04c7e3dc20395d450d8756&chksm=ec5ecd1cdb29440ad646667c8ad7b8fae4500dc58e5929b58c211323bc526fe3c9279ef6e12c&scene=27)
- [PyQt5自学攻略](https://blog.csdn.net/qq_20265805/article/details/82347071)
- [python使用pyqt写带界面工具](https://www.cnblogs.com/ydf0509/p/6820903.html)
- [PyQt5教程 Archi](https://www.cnblogs.com/archisama/default.html?page=2)

# 学习经验
PyQt毕竟是源自Qt。所以，如果实在找不到自己想要的学习资料，可以回头看下Qt的资料。        
QT的普及范围，比PyQt广太多了，学习资料也多太多了。大家可以对应找下自己需要的资料。      
只不过，QT是用C++开发的，大家对应转化一下就可以了。         
我个人很少通过视频学习，因为看视频学习效率太低，没有看文字效率快。      
不过，我个人一般不喜欢混群，因为混群的学习效率也很低。      

学习心法        
一句话：制心一处，无所不办      
八个字：多读，多想，多写，多改     

# PyQT5 的 模块
PyQt5是基于Digia公司强大的图形程式框架Qt5的python接口，由一组python模块构成。PyQt5本身拥有超过620个类和6000函数及方法。在可以运行于多个平台，包括：Unix, Windows, and Mac OS。      

QtCore QtGui QtWidgets QtMultimedia QtBluetooth QtNetwork QtPositioning Enginio QtWebSockets QtWebKit QtWebKitWidgets
QtXml QtSvg QtSql QtTest        

**QtCore模块**涵盖了包的核心的非GUI功能，此模块被用于处理程序中涉及到的 time、文件、目录、数据类型、文本流、链接、mime、线程或进程等对象。      
**QtGui模块**涵盖多种基本图形功能的类; 包括但不限于：窗口集、事件处理、2D图形、基本的图像和界面 和字体文本。        
**QtWidgets模块**包含了一整套UI元素组件，用于建立符合系统风格的classic界面，非常方便，可以在安装时选择是否使用此功能。      
**QtMultimedia模块**包含了一套类库，该类库被用于处理多媒体事件，通过调用API接口访问摄像头、语音设备、收发消息（radio functionality）等。        
**QtBluetooth模块**包含了处理蓝牙活动的类库，它的功能包括：扫描设备、连接、交互等行为。     
**QtNetwork模块**包含用于网络编程的类库，这组类程序通过提供便捷的TCP/IP 及 UDP 的 c/s 程式码集合，使得基于Qt的网络编程更容易。      
**QtPositioning模块**用于获取位置信息，此模块允许使用多种方式达成定位，包括但不限于：卫星、无线网、文字信息。此应用一般用于网络地图定位系统。       
**Enginio模块**用于构建客户端的应用程式库，用于在运行时访问 Qt Cloud 服务器托管的应用程序。     
**QtWebSockets模块**包含了一组类程序，用以实现websocket协议。       
**QtWebKit**包含了用于实现基于webkit2的网络浏览器的类库。       
**QtWebKitWidgets模块**包含用于基于WebKit1的Web浏览器实现的类，用于基于QtWidgets的应用程序      
**QtXml模块**包含了用于处理XML的类库，此模块为SAX和DOM API 的实现提供了方法。       
**QtSvg模块**通过一组类，为显示矢量图形文件的内容提供了方法。       
**QtSql模块**提供了数据库对象的接口以供使用     
**QtTest模块**包含了可以通过单元测试，以调试PyQt5应用程式的功能。       


# 安装使用
使用pip安装：`$ pip install pyqt5 -i https://www.douban.com/simple`
安装qt常用工具 Qt Designer, 国际化翻译工具 Liguist
```sh
$ pip install pyqt5-tools -i https://www.douban.com/simple
```
添加  pyqt5-tools 到环境变量
D:\Program\Python37\Lib\site-packages\pyqt5_tools


# Qt Designer
程序UI界面的的制作，可以用纯代码编写，也可以用Qt Designer制作。     
后者更方便灵活，前者或者更精准。    

Qt Designer 生成的UI界面是后缀为 `.ui` 的文件，Qt Designer 符合 MVC 模型视图控制器分离的设计模式，做到显示和业务逻辑分离。      
`.ui` 界面文件是 xml 格式，能够快速设计出程序界面，避免使用纯代码编写。     

将 `.ui` 文件 转换为 `.py` 文件: `$ pyuic5 -o firstMainWin.py firstMainWin.ui`

默认安装路径：%/Python37/Lib/site-packages/pyqt5_tools/designer.exe
新建窗体：Widget 通用窗口   Main Window 主窗口      
Main Window 模板默认添加了菜单栏、工具栏和状态栏    

Qt Designer 的区域介绍：        
Widget Box(工具箱) 可以直接拖放到主窗口，Crtl-R 预览    
Object Inspector(对象查看器) 查看主窗口放置的对象列表       
Property Editor(属性编辑器) 提供对窗口、控件、布局的属性编辑功能    
Signal/Slot Editor, Action Editor, Resource Browser     
信号/槽编辑器, 动作编辑器和资源浏览器
信号编辑器为控件添加自定义的信号和槽函数，编辑控件的信号和槽函数    
资源浏览器可以为控件添加图片，比如 Label, Button 的背景图片     

# 信号和槽
信号（signal)和槽（slot〕是Qt的核心机制在创建事件循环之后，通过建立信号和槽的连接就可以实现对象之间的通信。当信号发射（emit）时，连接的槽函数将会自动执行。在PyQt5中，信号和槽通过QObject.signal.connect()连接。       
所有从QObject类或其子类（如QWidget）派生的类都能够包含信号和槽。当对象改变其状态时，信号就由该对象发射出去。槽用于接收信号，但它们是普通的对象成员函数。多个信号可以与单个槽进行连接，单个信号也可以与多个槽进行连接。总之，信号和槽构建了一种强大的控件编程机制。  

对于新手来说，在学习信号与槽的过程中必须面对两个问题：第一个是PyQt5 默认有哪些信号与槽：第二个是如何使用这些信号与槽。      


# 自动化测试
手工测试是传统、常规的软件测试方法，由测试人员依据设计文档手工编写测试用例，然后执行并记录测试结果。对于手工测试，大部分测试人员再熟悉不过了，例如某个测试用例，是在页面中输入不同的值反复提交一个表单，对查询结果进行
测试，然后判断查询数据是否符合业务逻辑。这种测试方法适用于测试用例中输入项比较少的情况，如果需要不断地重复某个测试用例，例如不断地重复验证用户登录系统10000次后，是否还能登录系统成功，那么手工测试就会很累，这个时候就需要使用自动化测试来模拟手工登录系统的操作，从而避免重复的劳动。
自动化试是指利用软件测试工具自动实现全部或者部分测试工作（测试管理、

测试用例设计、测试执行和生成测试报告).自动化测试可节省大量的测试资源，并能够完成一些手工测试无法实现的测试，比如单元测试、统计测试覆盖率等。随着技术的进步，又发展出UI层的自动化测试。

UI层的自动化测试，是自动化测试的一类，是指编写代码、脚本，通过测试框架的驱动，让脚本自动运行，通过UI层面的键盘输入和鼠标操作，发现被测系统的缺陷，来代替部分手工测试。它的核心思想是，通过测试框架抓取被测元素对象，保存至对象库，通过脚本的编写以及配置必要的测试数据，在被测系统上进行回放，驱动被测系统完成我们期望的操作，获得最终结果，并将最终结果与预设的期望值进行比对，将比对结果进行报告输出。

综上所述，手工测试和自动化测试的特点总结如下：
（1)手工测试由人手工去执行测试用例；自动化测试由程序代替人去执行测试用例。	
（2）手工测试非常消耗时间，持续进行手工测试会使测试人员感到疲惫：自动化测试可以代替一部分机械重复的手工测试。		
（3）手工测试永远无法被自动化测试取代。在整个软件开发周期中，手工测试发现Bug所占的比例大，大约为80％；而自动化测试只能发现大约20％的Bug		
（4）手工测试适合测试业务逻辑；自动化测试适合进行回归测试。回归试用于测试己有功能，而不是新增功能。自动化测试有利于测试项目底层的细节，比如可以测试出软件的崩溃、API的错误返回值、业务逻辑异常和软件的内存使用等。		
