import QtQuick 2.12


Rectangle {
    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }
    Grid {
        x: 25; y: 25
        spacing: 4
        // 用重复器为Grid添加元素成员
        Repeater {
            model: 16   // 要创建元素成员的个数
            Rectangle {
                width: 48; height: 48
                color: "aqua"
                Text {
                    anchors.centerIn: parent
                    color: "black"
                    font.pointSize: 20
                    text: index
                }
            }
        }
    }
}
