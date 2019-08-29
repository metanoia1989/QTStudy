import QtQuick 2.0

Rectangle {
    width: 50; height:50
    color: "teal" // 蓝绿色
    MouseArea {
        anchors.fill: parent
        /* 拖拽属性设置 */
        drag.target: parent
        drag.axis: Drag.XAxis
        drag.minimumX: 0
        drag.maximumX: 360 - parent.width
        acceptedButtons: Qt.LeftButton|Qt.RightButton
        onClicked: { // 处理鼠标点击事件
            if (mouse.button === Qt.RightButton) {
                /* 设置矩形为蓝色并缩小尺寸 */
                parent.color = "blue";
                parent.width -= 5;
                parent.height -= 5;
            } else if ((mouse.button === Qt.LeftButton) && (mouse.modifiers & Qt.ShiftModifier)) {
                /*把矩形重新设为蓝绿色并恢复原来的大小 */
                parent.color = "teal";
                parent.width = 50;
                parent.height = 50;
            } else {
                /* 设置矩形为绿色并增大尺寸 */
                parent.color = "green";
                parent.width += 5;
                parent.height += 5;
            }
        }
    }
}
