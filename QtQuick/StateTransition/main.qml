import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("状态和切换")
    Rectangle {
        anchors.fill: parent
        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }
        Row {
            anchors.centerIn: parent
            spacing: 10
            StateText { text: "I" }		// 使用组件，要自定义其文本属性
            StateText { text: "love" }
            StateText { text: "QML" }
        }
    }
}
