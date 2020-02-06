import QtQuick 2.2

FocusScope {
    id: scope
    // FocusScope 需要绑定 Rectangle 的可视属性
    property alias color: rect.color
    x: rect.x; y: rect.y
    width: rect.width; height: rect.height

    Rectangle {
        id: rect
        anchors.centerIn: parent
        color: "lightsteelblue"; width: 175; height: 25
        radius: 10; antialiasing: true
        focus: true
        Text { id: label; anchors.centerIn: parent }
        Keys.onPressed: {
            if (event.key === Qt.Key_A) {
                label.text = "Key A was pressed!"
            } else if (event.key === Qt.Key_B) {
                label.text = "Key B was pressed!"
            } else if (event.key === Qt.Key_C) {
                label.text = "Key C was pressed!"
            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: { scope.focus = true }
        }
    }
}
