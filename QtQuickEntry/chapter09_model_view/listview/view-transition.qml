import QtQuick 2.12

ListView {
    width: 240; height: 320
    model: ListModel{
        ListElement { name: "Vue" }
        ListElement { name: "JS" }
        ListElement { name: "Lua" }
        ListElement { name: "QML" }
        ListElement { name: "C++" }
    }

    delegate: Rectangle {
        width: 100; height: 30; border.width: 1
        color: "lightblue"
        Text { anchors.centerIn: parent; text: name }
    }
    add: Transition {
        NumberAnimation {
            property: "opacity"
            from: 0; to: 1.0
            duration: 400
        }
        NumberAnimation {
            property: "scale"
            from: 0; to: 1.0
            duration: 400
        }
    }
    // 解决快速添加问题
    displaced: Transition {
        NumberAnimation {
            properties: "x, y"
            duration: 400
            easing.type: Easing.OutBounce
        }
        // 确保opacity和scale值变为1.0
        NumberAnimation { property: "opacity"; to: 1.0 }
        NumberAnimation { property: "scale"; to: 1.0 }
    }
}
