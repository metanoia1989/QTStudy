# 说明
这个目录下的代码主要是来自 Qt5 编程入门的示例

从Qt 4开始，Qt C++提供了一套完整的模型/视图架构进行数据的存储、处理和显示。其核心思想是数据和显示的分离，包含模型、视图和委托3部分，其中模型用于提供数据，视图负责显示数据，委托负责如何显示模型中具体的每一个数据项。在Qt Quick中也使用模型、视图和委托的概念来显示数据。这种开发架构将可视的数据模块化，从而让开发人员和设计人员能够分别控制数据的不同层面。例如，开发人员可以很方便地在列表视图和表格视图之间进行切换。而将数据实例封装进一个委托，可以使开发人员决定如何显示或处理这些数据。


# 11.1 模型彻图架构简介 
模型/视图架构中模型（Model）.视图（View）和委托（Delegate）之间的关系如下图所示。三者简单介绍如下：
* 模型：包含数据及其结构，有多种QML类型可以创建模型。
* 视图：用于显示数据的容器。数据可以以列表或者表格的形式显示出来。
* 委托：控制数据应该如何在视图中进行显示。委托获取并封装了模型中的每个数据，需要通过委托才能够访问到数据。

为了将数据可视化显示出来，需要将视图的`model`属性绑定到一个模型类型，然后将`delegate`属性绑定到一个组件或者其他兼容的类型。

关于委托的几个特点：
* 委托可以使用一个组件来实现。在委托中可以直接绑定数据模型中的角色，就是数据模型中每一个条目显示的时候，都会使用委托提供的显示方式进行显示。因而，委托可以看作是一个视图模板。
* 如果模型的属性名称和委托的属性名称出现了冲突，那么角色可以通过限定模型名称来访问。例如，如果这里委托中的Text元素也有一个type或者age属性，那么其 文本将会显示为它的属性值，而不会是模型中type和age的值。在这种情况下，可以使用`model.type`和`model.age`来确保委托中可以显示模型中的值。
* 委托还可以使用一个特殊的`index`角色，它包含了模型中条目的索引值。如果条目已经从模型中移除，那么其索引值为-1。所以如果在委托中绑定了`index`角色,那么一定要注意它的值有可能变为-1的情况。
* 如果模型中没有包含任何命名的角色，那么可以通过`modeData`角色来提供数据。对于只有一个角色的模型也可以使用`modelData`。这种情况下，ModelData角色与命名角色包含了相同的数据。
```js
Item {
    width: 200; height: 50

    ListModel {
        id: myModel
        ListElement { type: "Dog"; age: 8 }
        ListElement { type: "Cat"; age: 5 }
    }
    Component {
        id: myDelegate
        Text { text: type + ", " + age; font.pointSize: 12 }
    }
    ListView {
        anchors.fill: parent
        model: myModel; delegate: myDelegate
    }
}
```

# 11.2 数据模型
Qt Quick提供的模型类型位于QtQmL.Models模块中，需要先使用相应的导入语句来导入该模块。除了QtQmL.Models模块提供的通用模型之外，QML还提供了基于XML的QtQuick.XmlListModel模型和基于sqlite数据库的QtQuick.LocalStorage模型。

Models模块并不是QtQuick提供的，而是属于QML语言范畴。QML提供了3种内置的模型和两个供这些模型使用的辅助类型，如下表所列。除此之外，如果这些模型都不能满足需要，还可以使用Qt/C++定义模型。
*表 Model相关类型介绍*
模型	简介	导入语句
DelegateModel1	封装模型和委托	import QtQml. Models 2. 1
DelegateModelGroup2	封装经过过滤的可视数据项集合	
ListModel3	定义格式自由的列表式数据源	
ListElement4	定义使用在ListModel中的一个数据项	
ObjectModel5	定义作为模型使用的数据集合	
XmlListModel	使用XPath指定模型	import QtQuick. XmlListModel 2. 0
XmlRole	指定XmlListModel中的角色	

使用Repeater类型可以将模型中的数据在定位器`positioners`中进行布局并显示。
使用整数作为模型，其中包含了指定数量的委托类型。在这种情况下，模型中不包含任何数据角色。

## 11.2.1 ListModel
ListModel是一个简单的容器，可以包含ListElement类型存储数据。
* ListModel的数据项数目可以使用`count`属性获得。
* 为了维护模型中的数据，该类型还提供了一系列函数，包括追加`append()`、插入`insert()`、移动`move()`、移除`remove()`和替换`set()`等。这些函数都接受字典类型作为其参数，这种字典类型会被模型自动转换成ListElement对象。
* 如果需要通过模型修改ListElement中的内容，可以使用`setProperty()`函数，这个函数可以修改给定索引位置的ListElement的属性值。
* 注意，动态创建的内容一旦设置完成就不能再被修改。`setProperty`函数只能修改那些直接在模型中显式定义的元素的数据。

ListElement需要在ListModel中定义，表示能够在ListView或Repeater中使用的数据项。
* ListElement的使用同其他QML类型基本没有区别，不同之处在于，ListElement没有固定的属性，而是一系列自定义的键值。
* 可以把ListElement看作是一个键值对组成的集合，其中键被称为`role`（角色）。它使用与属性相同的语法进行定义。
* 角色既定义了如何访问数据，也定义了数据本身。角色的名字以小写字母开始，并且应当是给定模型中所有ListElement通用的名字。
* 角色的值必须是简单的常量：字符串（带有引号，可以包含在QT_TR_NOOP调用中）、布尔类型（true和false）.数字或枚举类型（例如AlignText.AlignHCenter）。
* 角色的名字供委托获取数据使用。每一个角色的名字都可以在委托的作用域内访问，并且指向当前ListElement中对应的值。 
* 角色还可以包含列表数据，例如包含多个ListElement。
```js
Item {
    width: 200; height: 150

    ListModel {
        id: fruitModel

        ListElement {
            name: "apple"; cost: 2.45
            attributes: [
                ListElement { description: "Core" },
                ListElement { description: "Decidous" }
            ]
        }
        ListElement {
            name: "Orange"; cost: 3.25
            attributes: [
                ListElement { description: "Core" },
                ListElement { description: "Decidous" }
            ]
        }
        ListElement {
            name: "Banana"; cost: 1.95
            attributes: [
                ListElement { description: "Tropical" },
                ListElement { description: "Seedless" }
            ]
        }
    }

    Component {
        id: fruitDelegate
        Item {
            width: 200; height: 50
            Text { id: nameField; text: name }
            Text { text: "$" + cost; anchors.left: nameField.right }
            Row {
                anchors.top: nameField.bottom; spacing: 5
                Text { text: "Attributes:" }
                Repeater {
                    model: attributes
                    Text { text: description }
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: fruitModel.setProperty(index, "cost", cost * 2)
            }
        }
    }

    ListView {
        anchors.fill: parent
        model: fruitModel; delegate: fruitDelegate
    }
}
```

## 11.2.2 WorkerScript
WorkerScript类型可以在新线程中执行一些操作，这样就可以将一些耗时的操作在后台运行，从而避免GUI主线程阻塞造成界面卡顿。使用该类型时，新的线程和父线程之间可以使用`sendMessage()`函数和`onMessage()`处理器来传递信息。传递的参数`message`可以是布尔类型、数字、字符串、JavaScript对象和数组、ListModel对象等。可以使用`source`属性指定实现了`onMessage()`处理器的JavaScript文件。

在数据视图编程中,当进行同步的数据修改等非常耗时的操作时，可以将ListModel结合WorkeScript，从多个线程访问列表模型。此时，列表的操作被移动到另外的线程,避免阻塞GUI主线程。
```js
Item {
    width: 150; height: 200

    ListModel {
        id: listModel
    }
    Component {
        id: delegate
        Text { id: nameField; text: time }
    }
    ListView {
        anchors.fill: parent
        model: listModel; delegate: delegate
    }
    WorkerScript {
        id: worker; source: "dataloader.js"
    }
    Timer {
        interval: 2000; repeat: true
        running: true; triggeredOnStart: true
        onTriggered: {
            var msg = {
                "action": "appendCurrentTime",
                "model": listModel
            };
            worker.sendMessage(msg);
        }
    }
}
// dataloader.js
WorkerScript.onMessage = function (msg) {
  if (msg.action === 'appendCurrentTime') {
    var data = { "time": new Date().toTimeString() };
    msg.model.append(data);
    msg.model.sync(); // 更新改动到列表
  }
}
```

## 11.2.3 ObjectModel
ObjectModel包含了用于在视图中进行显示的可视项目，也就是说，该类型可以将Qt Quick中的可视化项目作为数据显示到视图上。与ListModel不同，使用ObjectModel的视图不需要指定委托，因为ObjectModel已经包含了可视化的委托（项目）。可以使用`model`的附加属性`index`获取数据项的索引位置。
```js
import QtQuick 2.12
import QtQml.Models 2.12

Rectangle {
    ObjectModel {
        id: itemModel
        Rectangle { height: 30; width: 100; radius: 5; color: "red" }
        Rectangle { height: 30; width: 80;  color: "lightgrey" }
        Rectangle { height: 30; width: 150; radius: 10; color: "blue" }
        Rectangle { height: 30; width: 60; border.width: 3; color: "yellow" }
    }
    ListView {
        anchors.fill: parent; anchors.margins: 5
        model: itemModel
        spacing: 4
    }
}
```

## 11.2.4 DelegateModel
DelegateModel类型封装了一个模型和用于显示这个模型的委托，可以使用`model`属性指定模型，`delegate`属性指定委托。
* 一般情况下并不需要使用DelegateModel，如果需要将QAbstractItemModel的子类作为模型使用的时候，使用DelegateModel可以很方便地操作和访问 modelIndex。
* DelegateModel可以与Package一起，为多种视图提供委托，也可以与DelegateModelGroup一起用于排序和过滤委托元素。
* DelegateModelGroup类型提供了一种定位DelegateModel的委托项目的模型数据的方法，并且能够对委托项进行排序和过滤。
* DelegateModel可实例化委托项目的初始化集合由`DelegateModel::items`属性指定的组来表示。这个组通常会直接影响到分配给`DelegateModel::model`属性的模型中的内容。 
* 如果把`DelegateModel::groups`中定义的DelegateModelGroup对象的`name`属性分配给`DelegateModel::filterOnGroup`属性，那么初始化集合中的内容会被指定的DelegateModelGroup对象的内容替换。
* DelegateModelGroup定义了模型中数据的一个子集，可以用于对整个模型进行过滤。DelegateModel定义的DelegateModelGroup对象会为每一个委托项增加两个附加属性: `DelegateModel.in<GroupName>`（其中，`<GroupName>`是 DelegateModelGroup 对象的`name`属性定义的名称）保存该项属于哪一个组；`DelegateModel.<groupName>Index`保存该项在组中的索引。

DelegateModelGroup 还提供了一系列函数用于处理委托项的信息：
* 使用`get()`函数可以获取包含的数据项的信息；
* `move()`和`remove()`两个函数则可以辅助进行数据排序；
* `insert()`函数可以插入数据，这对在真实的数据准备完成之前添加占位符是非常有用的。

## 11.2.5 Package
Package类型可以结合DelegateModel，使委托可以为多个视图提供共享的上下文。在Package中的任何项目都会通过Package.name附加属性分配一个名称。
这里使用Package作为DelegateModel的委托，里面包含了两个命名的项目`list`和`grid`。
```js
DelegateModel {
    id: delegateModel
    delegate: Package {
        Text {
            id: listDelegate;
            width: parent.width;
            height: 25;
            text: "in list";
            Package.name: "list"
        }
        Text {
            id: gridDelegate;
            width: parent.width / 2;
            height: 50;
            text: "in grid";
            Package.name: "grid"
        }
    }
    model: 5
}
```


## 11.2.6 XmlListModel
XmlListModel 可以从XML数据创建只读的模型，即可以作为视图的数据源，也可以为`Repeater`等能够和模型数据进行交互的类型提供数据。

XmlListModel的source属性定义为一个远程XML文档，能够自动获取这个远程数据。
XmlRole对象定义模型中每一个数据条目的特性。还需要指定值的类型。

由于XmlListModel的数据是异步加载的，因此当程序启动、数据尚未加载的时候，界面会显示一段时间的空白。

可以使用`XmlListModel::status`属性判断模型加载的状态。该属性可取的值为：
* `XmlListModel.Null`：模型中没有 XML 数据；
* `XmlListModel.Ready`：XML数据已经加载到模型；
* `XmlListModel.Loading`: 模型正在读取和加载XML数据；
* `XmlListModel.Error`：加载数据出错，详细出错信息可以使用`errorString()`函数获得。

由于XmlListModel是只读模型，当原始XML数据发生改变时，可以通过调用`reload()`函数刷新模型数据。此时，模型并不会刷新所有数据，而是仅仅更新那些标记为“关键”的数据。可以使用`XmlRole::isKey`属性，标记一个角色是关键的。
```js
XmlRole { name: "pubDate"; query："pubDate/string()"; isKey: true }
```

当调用`reload()`时，模型只会添加和重新加载模型中那些“pubDate”值没有显示的条目。这对于显示增量更新内容的XML文档(例如RSS订阅)是十分有用的，可以避免在视图中重绘模型中的全部内容。
```js
import QtQuick 2.12
import QtQuick.XmlListModel 2.12

Rectangle {
    width: 500; height: 340

    XmlListModel {
        id: xmlModel
        source: "http://www.people.com.cn/rss/edu.xml"
        query: "/rss/channel/item"
        XmlRole { name: "title"; query: "title/string()" }
        XmlRole { name: "pubDate"; query: "pubDate/string()" }
    }

    ListView {
        width: 180; height: 300
        model: xmlModel
        delegate: Text { text: title + ": " + pubDate }
        spacing: 5
    }
}
```

## 11.2.7 LocalStorage
LocalStorage是一个用于读取和写入SQLite数据库的单例类型，可以使用`openDatabaseSync()`打开一个本地存储的SQL数据库。这些数据库是特定于用户的，也是特定于QML的，但是可以被所有QML应用程序访问。数据库保存在`QQmlEngine::offlineStoragePath()`返回的子文件夹Databases中。数据库的链接无需手动释放，事实上，它们会被JavaScript的垃圾收集器自动关闭。

LocalStorage模块的API与HTML 5 Web Database API 兼容。模块中所有API都是异步的，每一个函数的最后一个参数都是该操作的回调函数。如果不关心这个回调函数，可以简单地忽略该参数。

### 1. 打开数据库
```js
import QtQuick.LocalStorage 2.12 as Sql
db = Sql.openDatabaseSync(identifier, version, description, estimated_size, callback(db))
```
`openDatabaseSync()`函数返回数据库标识符为identifier的数据库。如果数据库不存在，将会自动创建。回调函数callback以该数据库作为参数。当数据库创建失败时，callback函数才会被回调。参数`description`和`estimatedSize`将被写入INI文件，不过这两个参数现在都没有使用。函数可能会抛出异常，异常代码为`SQLException.DATABASE_ERR`或`SQLException.VERSION_ERR。

数据库创建完成之后，系统会创建一个INI文件，用于指定数据库的特性，如下表所列。这些数据能够被应用程序工具使用。
键 |	值
----|----
Name |	传入openDatabaseSync函数的数据库名字
Version |	传入openDatabaseSync函数的数据库版本
Description |	传入openDatabaseSync函数的数据库描述
EstimatedSize |	传入openDatabaseSync函数的数据库预计大小(单位：字节)
Driver |	现在值为QSQLITE

### 2. 更改版本
```js
db.changeVersion(from, to, callback(tx))
```
该函数使用`openDatabaseSync`的返回值进行调用，允许数据库进行模式升级(Schema Update)。如果函数正常执行，系统会创建一个事务，并将其作为参数`tx`传给`callback`回调函数。在回调函数中，可以调用参数`tx`的`executeSql`函数升级数据库。如果当前数据库版本与参数`from`不同，函数会抛出异常；异常代码可能是`SQLException.DATABASE_ERR`或`SQLException.UNKNOWN_ERR`。

### 3. 读/写事务
```js
db.transaction(callback(tx))
```
该函数使用`openDatabaseSync`的返回值进行调用，会创建一个可供读/写的事务，并将其传递给`callback`回调函数。在回调函数中，可以调用参数`tx`的`executeSql`函数 读取和修改数据库(SELECT、INSERT、UPDATE和DELETE语句)。如果回调函数抛出异常，事务将回滚。

### 4. 只读事务
```js
db.readTransaction(callback(tx))
```
该函数使用`openDatabaseSync`的返回值进行调用，会创建一个只读的事务，并将其传递给`callback`回调函数。在回调函数中，可以调用参数`tx`的`executeSql`函数读取数据库(SELECT语句)。

### 5.执行SQL语句
```js
results = tx.executeSql(statement, values)
```
该函数使用一个事务对象进行调用，能够执行一条SQL语句statement，使用`?`作为占位符，将`values`参数绑定到SQL语句。函数返回值是一个对象，包含的属性如下表所列。
类型  |	属性  |	值 |	适用于
---|---|---|---
int |	rows.length |	结果集行数 |	SELECT
var |	rows.item(i) |	返回结果集第i行的数据 |	SELECT
int |	rowsAffected |	修改数据时受影响的行数 |	UPDATE. DELETE
string |	insertId | 	被插入的行的id |	INSERT

该函数可能抛出异常，异常代码是`SQLException.SYNTAX_ERR`或`SQLException.UNKNOWN_ERR`。

最终示例程序，但是最后查询的 rs.rows 是空对象。=_= 咋回事。
```js
import QtQuick 2.9
import QtQuick.LocalStorage 2.12

Rectangle {
    width: 200; height: 100

    Text {
        text: "?"
        anchors.horizontalCenter: parent.horizontalCenter

        Component.onCompleted: findGreetings()

        function findGreetings() {
            let db = LocalStorage.openDatabaseSync(
                "QQmlExampleDB", "1.0", "The Example QML SQL!", 1000000)
            db.transaction((tx) => {
                // 如果数据库不存在则创建数据库
                tx.executeSql("CREATE TABLE IF NOT EXISTS Greeting (salutation TEXT, salutee TEXT)")
                // 添加一条记录
                let result = tx.executeSql("INSERT INTO Greeting VALUES(?, ?)", ["hello", "world"]);
                tx.executeSql("INSERT INTO Greeting VALUES(?, ?)", ["hello", "qml"]);
                tx.executeSql("INSERT INTO Greeting VALUES(?, ?)", ["hello", "c++"]);
                // 显示内容
                let rs = tx.executeSql("SELECT * FROM Greeting");
                let r = "";
                for (let row of rs.rows) {
                    r += row.salutation + "," + row.salutee + "\n";
                }
                text = r;
            });
        }
    }
}
```

## 11.2.8 使用C++扩展QML模型
虽然QML已经提供了几种比较常见的模型，但是依然不足以应对应用中可能出现的情况。为了解决这一问题，可以先使用C++定义模型，然后在QML中使用该模型，这有助于将C++数据模型或其他复杂的数据集暴露给QML。

C++模型类可以是QStringList、QObjectList或者QAbstractItemModel。前面两个对于暴露简单数据集非常有用，而QAbstractItemModel则为更复杂的模型提供了灵活的解决方案。

### 1. QStringList
QStringList可以作为一个简单的模型，在视图中使用`modelData`角色读取模型中的数据。为了在视图中使用QStringList，首先要在C++代码中创建一个作为模型的QStringList对象。利用`QQmlApplicationEngine`获得QML引擎，然后使用`rootContext()`函数获取引擎的根上下文，最后创建的模型对象暴露给视图，设置为上下文的stringListModel属性。

这里可以像使用普通的QML模型类型一样来使用stringListModel。注意，目前版本暂时无法在QStringList有变化时通知视图更新，这是与QML内置模型不同之处。所以，如果QStringList发生变化，需要重新调用`QQmlContext::setContextProperty()`函数。另外，在使用这个函数时注意应该在`QQmlApplicationEngine::load()`函数之前调用，否则会有警告。
```cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QStringList dataList;
    dataList.append("Item 1");
    dataList.append("Item 2");
    dataList.append("Item 3");
    dataList.append("Item 4");
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("stringListModel",
                                QVariant::fromValue(dataList));

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
// qml
ListView {
    anchors.fill: parent
    model: stringListModel
    delegate: Rectangle {
        height: 25; width: 100
        Text { text: modelData }
    }
}
```

### 2. QVariantList
使用方法与QStringList的模型类似。

### 3. QObjectList
QObjectList列表也可以作为模型使用。与ObjectModel类似，QObjectList提供了可以用于模型的一个对象列表。
注意，与QStringList相同，目前版本暂时无法在QObjectList有变化时通知视图 更新。
```c++
#include <QObject>

class DataObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)

public:
    explicit DataObject(const QString &name, const QString &color,
                        QObject *parent = nullptr);
    void setName(const QString &name);
    QString name() const;

    void setColor(const QString &color);
    QString color() const;

signals:
    void nameChanged(const QString &name);
    void colorChanged(const QString &color);

private:
    QString mName;
    QString mColor;
};
// main.cpp
QObjectList objectList;
objectList.append(new DataObject("Item1", "red"));
objectList.append(new DataObject("Item2", "green"));
objectList.append(new DataObject("Item3", "blue"));
objectList.append(new DataObject("Item4", "yellow"));
QQmlContext *context = engine.rootContext();
context->setContextProperty("objectListModel",
                            QVariant::fromValue(objectList));
```

### 4. QAbstractItemModel
可以通过子类化QAbstractItemModel定义一个模型，如果要使用其他方式都无法支持的复杂模型时，这是最好的选择。与QStringList和QObjectList不同，QAbstractItemModel的模型数据在发生变化时可以自动通知QML视图。QAbstractItemModel子类中的角色可以通过重新实现`roleNames()`来暴露给QML。

如果需要自定义模型发生改变时，视图自动刷新，必须严格遵守模型约定，即在模型数据发生改变是发出`QAbstractltemModel::dataChanged()`信号、使用`QAbstractltemModel::beginInsertRows()`函数等。

虽然QAbstractltemModel能够存储带有层次结构的表格数据，但是现在版本的QML视图只能处理列表数据。为了显示层次模型中的子列表，需要使用DelegateModel类型。该类型提供了一系列属性和函数，用于结合QAbstractltemModel类型列表使用。

# 11.3视图类型
视图作为数据项集合的容器，不仅提供了强大的功能，还可以进行定制来满足样式或行为上的特殊需求。视图类型继承自Flickable类型，在数据量超出窗口范围时，用户可以进行拖动以显示更多的数据。

Qt Quick模块中提供了一组标准视图类型，如下表所列。
视图 |	简介
----|----
ListView |	提供模型的列表显示
GridView |	提供模型的表格显示
PathView |	使模型按照一定的路径进行显示
Path |	配合PathView使用，用于定义路径

## 11.3.1 ListView
ListView可以以水平或垂直形式显示列表。

### 1. 布局
在ListView中的项目可以使用下面的属性进行布局：
* `orientation`：控制项目的排列，可选值为水平 ListView.Horizontal 或垂直 ListView.Vertical。
* `layoutDirection`：当水平显示列表时，ListView默认从左向右显示数据，使用该属性可以改变数据的显示方向，可选Qt.LeftToRight或Qt.RightToLeft 两个值，选择后者可以从右向左显示数据。
* `verticalLayoutDirection`：当垂直显示列表时，默认从上向下显示数据，使用该属性可以改变数据的显示方向，可选ListView.TopToBottom或ListView.BottomToTop两个值，选择后者可以从下向上显示数据。

ListView允许使用自定义的可视组件作为视图的头部和脚部。如果是水平的ListView, 头部和脚部元素显示在第一个数据项之前和最后一个数据项之后，具体的位置取决于layoutDirection属性的值。添加头部和脚部与设置`delegate`类似，只需将元素绑定到`header`属性和`footer`属性，而使用headeritem和footeritem可以获取创建的头部和脚部组件。


ListView的`spacing`属性可以设置显示的条目之间的间距，但是头部和脚部并不使用这个间距，只会紧贴着第一个或最后一个数据项。如果需要为头部或脚部添加间距,这些间距只能由头部或脚部组件提供。

因为ListView继承自Flickable类型，所以它默认是可以被拖拽进行滚动的，`snapMode`属性可以设置ListView的滚动行为。
`snapMode`不会影响`currentindex`属性，这个属性依然会返回当前项目的索引。
`snapMode`属性的可选值为：
* ListView.NoSnap：默认值，视图可以停止在可视区域的任意位置。
* ListView.SnapToItem：视图在滚动停止时，有一个条目会与视图开始位置对齐。
* ListView.SnapOneltem：视图不会快速滚动，而停止时停留的位置比鼠标释放时的可视项目的位置不会多出一个项目。这个模式常用于一次移动一页。


### 2. 键盘导航和高亮
使用键盘控制视图，需要设置`focus`属性为true，以便ListView能够接收键盘事件。还可以设置`keyNavigationWraps`属性为true，这样当使用键盘导航时如果到达列 表的最后一个数据项，会自动跳转到列表的第一个数据项。

`highlight`属性可以设置一个组件作为高亮，会为每一个列表创建一个该高亮组件的实例。实际的组件实例的几何形状是被列表管理的，以便该高亮留在当前项目，除非将`highlightFollowsCurrentItem`属性设置为false。高亮项目的默认z值是0。

默认情况下，ListView负责移动高亮项的位置。可以自行设置高亮项的移动速度和改变大小的速度，可用的属性有`highlightMoveVelocity`、`highlightMoveDuration`、`highlightResizeVelocity` 和`highlightResizeDuration`。前二者分别以速度值和间隔时间设置高亮项移动速度；后两者分别以速度值和间隔时间设置高亮项大小改变的速度。 默认情况下，速度值为每秒400像素，间隔时间值为-1。如果同时设置速度值和间隔时间，则取二者之中较快的一个。要使用这4个属性，必须保证`highlightFollowsCurrentltem`为true才会有效果。

ListView会在委托的根项目中附加多个属性，例如`ListView.isCurrentltem`。

在委托组件的根项目Rectangle中可以直接使用`ListView.isCurrentltem`附加属性获取当前项目，而在子对象Text中，必须使用`wrapper.ListView.isCurrentltem`才可以使用该属性。

视图的`clip`属性默认是false，如果想要其他项目或者屏幕对超岀的内容进行裁剪，需要将该属性设置为true。

当使用高亮时，可以使用一系列属性控制高亮的行为。`preferredHighlightBegin`属性和`preferredHighlightEnd`属性用来设置高亮（当前项目）的最佳范围，前者必须小于后者。它们可以在列表滚动时影响当前项目的位置，例如在列表滚动时当前选择的项目要保持在列表的中间，可以将`preferredHighlightBegin`和`preferredHighlightEnd`分别设置为中间项目的顶部坐标和底部坐标。不过它们还受到`highlightRangeMode`属性的影响，该属性的可选值为：
* `ListView.ApplyRange`：视图尝试将高亮保持在设置的范围内，但是在列表的末尾或者与鼠标交互时可以移出设置的范围。
* `ListView.StrictlyEnforceRange`：高亮不会移出设置的范围。如果使用键盘或者鼠标引起高亮要移出设置的范围，当前项可能改变，从而保证高亮不会移出设置的范围。
* `ListView.NoHighlightRange`：默认值，没有设置范围。

为了获得高亮项更多的控制权，可以将`highiightFollowsCurrentltem`属性设置为false。这意味着视图不再负责高亮项位置的移动，而是交给高亮组件本身来进行处理。 
```js
Item {
    width: 80; height: 370
    ListView {
        id: listview;
        anchors.fill: parent; anchors.margins: 30
        spacing: 5; clip: true
        model: 20;
        delegate: numberDelegate; snapMode: ListView.SnapToItem
        header: Rectangle {
            width: 50; height: 20; color: "#b4d34e"
            Text { anchors.centerIn: parent; text: "header" }
        }
        footer: Rectangle {
            width: 50; height: 20; color: "#797e65"
            Text { anchors.centerIn: parent; text: "footer" }
        }
        highlight: Rectangle { color: "black"; radius: 5; opacity: 0.3; z: 5 }
        focus: true; keyNavigationWraps: true
        highlightMoveVelocity: 100
    }

    Component {
        id: numberDelegate
        Rectangle {
            id: wrapper; width: 50; height: 50;
            color: ListView.isCurrentItem ? "white" : "lightGreen"
            Text {
                anchors.centerIn: parent; font.pointSize: 15; text: index
                color: wrapper.ListView.isCurrentItem ? "blue" : "white"
            }
        }
    }
}
```


### 3.数据分组
ListView支持数据的分组显示：相关数据可以出现在一个分组中。每个分组还可以使用委托定义其显示的样式。
ListView定义了一个`section`附加属性，用于将相关数据显示在一个分组中，`section`是一个分组属性，其属性包含:
* `section.property`：定义分组的依据，也就是根据数据模型的哪一个角色进行 分组；
* `section.criteria`：定义如何创建分组名字，可选值是：
 * `ViewSection.FullString`：默认，依照`section.property`定义的值创建分组；
 * `ViewSection.FirstCharacter`：依照`section.property`值的首字母定义分组；
* section.delegate：与ListView::delegate类似，用于提供每一个分组的委托组件，其z属性值为2。
* section.labelPositioning：定义当前或下一个分组标签的位置，可选值是：
 * ViewSection.InlineLabels：默认，分组标签出现在数据项之间；
 * ViewSection.CurrentLabelAtStart:在列表滚动时，当前分组的标签始终出 现在列表视图开始的位置；
 * ViewSection.NextLabelAtEnd:在列表滚动时，下一分组的标签始终岀现在 列表视图末尾。该选项要求系统预先找到下一个分组的位置，因此可能会有 一定的性能问题。

ListView 中的每一个数据项都有 ListView.section、ListView.previousSection 和 ListView.nextSection等附加属性。

## 11.3.2 GridView
GridView在一块可用的空间中以方格形式显示数列表。GridView和ListView非常类似，实质的区别在于,GridView需要在一个二维表格视图中使用委托，而不是线性列表中。
相比较ListView, GridView并不建立在委托的大小及其之间的间距之上。GridView使用cellWidth和cellHeight属性控制单元格的大小。每一个委托所渲染的元素 都会出现在这样一个单元格的左上角。

GridView也可以包含头部和脚部以及使用高亮委托，这与ListView是类似的；还可以使用`flow`属性 设置GridView的方向，可选值为：
* `GridView.FlowLeftToRight`：默认值，表格从左向右开始填充，按照从上向下的顺序添加行。此时，表格是纵向滚动的。
* `GridView.FlowTopToBottom`：表格从上向下开始填充，按照从左向右的顺序添加列。此时，表格是横向滚动的■

## 11.3.3 视图过渡
在ListView和GridView中，因为修改了模型中的数据，需要更改视图上的项目时, 可以指定一个过渡使视图的变化出现动画效果。可以使用过渡的属性有:populate、add、remove、move、displaced、addDisplaced、removeDisplaced和moveDisplaced等。

每当按下空格键的时候，都会向模型中添加一个数据项。在视图中为添加`add`和移位`displaced`操作设置了过渡效果，所以每当添加数据项时都会有动画效果。注意, 这里的Number Animation对象并不需要指定`target`和`to`属性，因为视图已经隐式的将`target`设置为对应的项目，将`to`设置为了该项目最终的位置。

前面这样只是最简单的应用，如果想要为视图中的单个数据项定制不同的过渡动画，需要使用`ViewTransition`附加属性。这个附加属性会为使用了过渡的项目提供如下属性：
* ViewTransition.item：过渡中的项目；
* ViewTransition.index：该项目的索引；
* ViewTransition.destination：该项目要移动到目标位置(x, y)；
* ViewTransition.targetindexes：目标项目的索引(目标项目可能不止一个);
* ViewTransition.targetitems：目标项目本身。

表11-5 ViewTransition属性值介绍
属性	值	说明
ViewTransition. item	"Item。”委托实例	“Item 0**Rectangle 对象本身
ViewTransition. index	int类型数值4	“Item。”在模型中的索引
ViewTransition. destination	point 类型值（0, 120）	“Item 0”要移动到的位置
ViewTransition. targetindexes	int数组，只包含了整数0	新添加到视图的“Item 4”的索引
ViewTransition. targetitems	对象数组，只包含了“I- tem 4”委托实例	新添加到视图的“Item 4”的Rectangle对象

### 1. 基于索引的延迟动画
实现效果是为移位的项目提供波纹类型的动画效果，可以通过在displaced过渡中 延时每一个项目的动画来实现。延时可以通过每个项目的索引`ViewTransition.index` 和目标索印`ViewTransition.targetindexes`之间的差值来设置。

### 2.项目移向中间的动画效果
视图过渡的`ViewTransition.item`属性提供了应用过渡效果的项目的一个引用， 可以通过该引用访问项目的任何特性，例如property属性值。在前面的延迟动画效果上进行修改，通过在过渡的开始访问每一个项目的x和y值，实现了每个项目从开始位 置动态移动到中间位置，然后回到最终位置的动画效果。

### 3.处理中断动画
一个视图过渡有可能在任意时刻被其他过渡打断。如果只进行简单的过渡，无需考虑动画中断的情况。但是，如果过渡中更改了一些属性，那么中断可能会引起不可预料的后果。

同样的原则适用于任何视图过渡组合。例如，在添加过渡动画没有结束以前就开始了移动，或者在移动动画没有结束以前就进行了移出等。处理这些情况的原则就是 每一个过渡都要处理相同的属性集。

## 11.3.4 PathView
PathView是Qt Quick提供的最强大最复杂的视图，能够将所有委托实例在一个特定的路径上布局。基于这个路径，视图还能够进行缩放、其他细节调整等。在使用PathView 时，需要定义一个委托和一个路径path。另外，PathView还提供了一系列属性用于控制视图。例如，pathltemCount属性定义了在路径上每次显示的项目数量；cacheltemCount属性定义了路径上缓存的项目数量，缓存一些项目可以使视图滚动更流畅。

PathView同样可以使用`highlight`属性设置高亮，不过需要在可视组件中将`visible`属性设置为`PathView.onPath`附加属性。这是因为设置了 `pathItemCount`以后，一些项目已经被实例化了，但是当前可能没有出现在路径上，一般会将这样的项目设置为不可见。在PathView中，`preferredHighlightBegin`和`preferredHighlightEnd`两个属性很重要，它们取值范围均为0.0〜1.0。如果需要当前项始终出现在路径的中间， 可以将两个属性都设置为0.5，并且在PathView中的highlightRangeMode默认值为 PathView. StrictlyEnforceRange „

PathView并不会自动处理键盘导航，因为导航的按键会依赖于路径的形状。要设置导航按键，需要先设置focus属性为true，然后调用`decrementCurrentlndex()`或`incrementCurrentIndex()`函数。 


### 1. 路径path
路径path属性需要指定一个path类型对象。 path类型使用`startX`属性和`startY`属性定义路径的起点，具体路径则由被添加到默认属性 `pathElements`中的路径元素对象定义。可以被添加到`pathElements`属性的路径元素为：
* PathLine：到给定位置的一条直线。
* PathQuad：到给定位置的一条二次贝塞尔 曲线，包含一个控制点。
* PathCubic：到给定位置的一条三次贝塞尔 曲线，包含两个控制点。
* PathArc：到给定位置的一段弧，包含一个半径。
* PathSvg：由SVG路径数据字符串定义的一段路径。
* PathCurve: Catmull-Rom曲线上的一点。
* PathAttribute：路径上给定位置的特性。
* PathPercent：定义在路径上项目的分布方式。

其中，PathLine、PathQuad、PathCubic、PathArc、PathCurve、PathSvg 等路径元素对象用于定义实际的路径;
PathPercent和PathAttribute对象则用于对创建的路径进 行调整。

### 2. 路径特征
PathAttribute类型允许在路径的任意点指定一个包含了名称和值的特性，该特性会作为附加属性暴露给视图的委托。

### 3. 路径分布
PathPercent类型可以控制路径上项目的间距，从而控制项目的分布密度。该类型只有一个value属性，用来设置到达路径上特定点时项目数量所占的比例。注意路径上后面位置设置的`PathPercent`的值一定要比前面位置设置的值大。

# 11.4调整性能
模型视图的性能问题，很大程度上取决于准备新的委托时耗费的时间。当向下滚动ListView时，新的委托被添加到视图下方新进入可视范围的区域，旧有的委托则从视图上方离开可视范围的位置被移除。如果委托需要耗费很长时间进行初始化，当用户快速地滚动视图时，这个过程就变得明显起来。我们可以通过将`clip`属性设置为false观察到这一点。

为了解决这一问题，可以协调滚动视图的边距。通过设置`cacheBuffer`属性可以达到这一目的。在快速向下滚动的过程中，视图将计算上下两侧有多少像素能够包含准备好的委托。

分配给委托的内存越多，就越能提供一种平滑的滚动体验，但是也会略微增加每一个委托的初始化时间。对于非常复杂的委托，这并不是一个很好的解决方案。因为委托的初始化要求其内容要全部计算完成，这需要消耗一定的时间。如果消耗时间过多，则会降低滚动体验。一个委托中的子对象过多，即使初始化完成，在之后的滚动过程中也会降低滚动性能。

为了解决后面两个问题，推荐使用Loader类型。Loader类型不仅在需要时才加载额外的组件。例如一个可以被展开的委托使用Loader类型加载展开之后的视图。只有当用户进行展开操作时，Loader对应的视图才会被加载。基于同样的原因，不要在委托中执行复杂的JavaScript代码。尽可能将JavaScript代码放在委托之外，这可以减少创建委托时编译JavaScript代码所消耗的时间。

# 11.5小结
利用模型视图可以轻松完成以数据为中心的程序开发，配合动画、状态和过渡等相 关类型，可以设计出流畅的数据展示界面。本章讲解了模型视图相关内容在QML编 程中的使用，尽可能让读者明白模型视图框架的基本原理和使用方法，但是并没有对模 型视图和SQLite等内容进行深入讲解。要了解相关内容还是要参考《Qt Creator快速 入门（第2版）》的相关章节。


