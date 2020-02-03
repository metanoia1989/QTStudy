import QtQuick 2.0

Rectangle {
    id: rect
    property color previousColor
    property color nextColor
    nextColor: "red"
    width: 100
    height: 100
    color: nextColor
    onNextColorChanged:
        console.log("The next color will be: " + nextColor.toString())
    Component.onCompleted: {
        rect.height *= 2
        rect.width *= 2
    }

    MouseArea {
        anchors.fill: parent
        onClicked: nextColor = "yellow"
    }
    Item {
        // 除enumeration外，QML的基本类型都可以用作自定义属性的类型
        property int someNumber
        property string someString
        property url someUrl
    }
    Item {
        // var是一种通用的占位符类型，类似于QVariant，它可以包含任意类型的值，包括列表和对象。
        property var someNumber: 1.5
        property var someString: 1.5
        property var someBool: true
        property var someList: [1, 2, "three", "four"]
        property var someObject: Rectangle {
            width: 100;
            height: 100;
            color: "red"
        }
        // OML对象类型也可以作为一个属性类型。
        property Item someItem
        property Rectangle someRectangle
    }
}
