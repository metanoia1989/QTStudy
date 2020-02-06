import QtQuick 2.2

// 红色矩形只能在父对象的水平方向上移动，在移动的同时改变透明度。
Rectangle {
    id: container
    width: 600; height: 200
    Rectangle {
        id: rect
        width: 50; height: 50
        color: "red"
        opacity: (600.0 - rect.x) / 600
        MouseArea {
            anchors.fill: parent
            drag.target: rect
            drag.axis: Drag.XAxis
            drag.minimumX: 0
            drag.maximumX: container.width - rect.width
        }
    }
}