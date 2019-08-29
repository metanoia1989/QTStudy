import QtQuick 2.0

Rectangle { // 将 Rectangle 自定义为按钮
    id: btn
    width: 100; height: 62
    color: "teal"
    border.color: "aqua"
    border.width: 3

    Text {
        id: label
        anchors.centerIn: parent
        font.pointSize: 16
        text: "开始"
    }

    MouseArea { // MouseArea 对象作为按钮点击事件响应区
        anchors.fill: parent
        onClicked: {
            label.text = "按钮已按下！"
            label.font.pointSize = 11 // 改变按钮文字和字号
            btn.color = "aqua"	// 改变按钮颜色
            btn.border.color = "teal" // 改变按钮边界色
            /* 改变 changingRect1 的右锚属性 */
            chgRect1.anchors.left = undefined
            chgRect1.anchors.right = rRect.right
            /* 改变 changingRect2 的右锚属性 */
            chgRect2.anchors.left = undefined
            chgRect2.anchors.right = rRect.right
        }
    }
}
