import QtQuick 2.0

Text {	// 这是一个具有状态改变能力的 Text 元素
    id: stext
    color: "grey"
    font.family: "Helvetica"
    font.pointSize: 12	// 初始字号
    font.bold: true	// 加粗
    MouseArea {
        id: mArea
        anchors.fill: parent
    }
    states: [
        State {
            name: "highlight"
            when: mArea.pressed
            PropertyChanges {
                target: stext
                color: "red"
                font.pointSize: 25	// 字号放大
                style: Text.Raised	// 以艺术字呈现
            }
        }
    ]
    transitions: [
        Transition {
            PropertyAnimation {
                duration: 1000
            }
        }
    ]
}
