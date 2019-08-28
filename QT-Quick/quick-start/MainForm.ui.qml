import QtQuick 2.4


Rectangle {	// 根对象
    property alias mouseArea: mouseArea // 属性别名
    property alias textEdit: textEdit
    property type name: value

    width: 360 // 属性 宽度
    height: 360 // 属性 高度

    MouseArea {	// 子对象1
       id: mouseArea 	// 对象标识符
       anchors.fill: parent
    }

    TextEdit {
        id: textEdit
        text: qsTr("输入一些文本...")
        verticalAlignment: Text.AlignVCenter
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20

        Rectangle {
            anchors.fill: parent
            anchors.margins: -10
            color: "transparent"
            border.width: 1
        }
    }
}
