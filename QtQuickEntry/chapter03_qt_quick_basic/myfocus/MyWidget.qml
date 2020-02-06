import QtQuick 2.2

Rectangle {
    id: widget
    color: "lightsteelblue"; width: 175; height: 25
    radius:10; antialiasing: true
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
}