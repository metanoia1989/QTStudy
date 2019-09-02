import QtQuick 2.0

FocusScope {
    property alias label: label.text
    property alias text: input.text

    Row {
        spacing: 5
        Text { 	// 输入提示文j本
            id: label
            text: "标签"
        }
        Rectangle {
            width: 100
            height: 20
            color: "white" 	// 白底色
            border.color: "gray" // 灰色边框
            TextInput {
                id: input
                anchors.fill: parent // 充满矩形
                anchors.margins: 4
                focus: true
                text: "请输入内容..."  // 初始文本
            }
        }
    }
}
