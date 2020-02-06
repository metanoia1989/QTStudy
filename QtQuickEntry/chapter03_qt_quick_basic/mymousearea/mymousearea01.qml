import QtQuick 2.2

Rectangle {
    color: "yellow"
    width: 100; height: 100
    MouseArea {
        anchors.fill: parent
        onClicked: console.log("clicked yellow")
        onDoubleClicked: {
            console.log("double clicked yellow")
            mouse.accepted = false
        }
    }
    // 设置了 propagateComposedEvents 为 true,并且 clicked 和 doubleClicked 事件的MouseEvent.accepted 设置为了 false
    // 所以蓝色矩形所有的单击和双击事件都会传播到黄色矩形。
    Rectangle {
        color: "blue"
        width: 50; height: 50
        MouseArea {
            anchors.fill: parent
            propagateComposedEvents: true
            onClicked: {
                console.log("clicked blue")
                mouse.accepted = false
            }
            onDoubleClicked: {
                console.log("double clicked blue")
                mouse.accepted = false
            }
        }
    }
}
