import QtQuick 2.12

Rectangle {
    id: root
    width: 48; height: 48
    color: "green"
    signal	clicked
    property bool active: false
    border.color: active ? "#666666" : "#f0f0f0"
    border.width: 2

    MouseArea {
        id: area
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
