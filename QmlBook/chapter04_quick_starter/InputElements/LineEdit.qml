import QtQuick 2.12

Rectangle {
    width: 96; height: input.height + 8
    color: "lightsteelblue"
    border.color: "gray"

    property alias text: input.text
    property alias input: input

    TextInput {
        id: input
        height: 20
        anchors.fill: parent
        anchors.margins: 4
        focus: true
    }
}
