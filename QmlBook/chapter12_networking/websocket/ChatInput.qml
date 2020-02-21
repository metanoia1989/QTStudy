import QtQuick 2.12

FocusScope {
    id: root
    width: 240
    height: 32
    property alias text: input.text
    signal accepted(string text)

    Rectangle {
        anchors.fill: parent
        color: "#000"
        border.color: "#fff"
        border.width: 2
    }

    TextInput {
        id: input
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 4
        anchors.rightMargin: 4
        color: "#fff"
        focus: true
        onAccepted: root.accepted(text)
    }
}
