import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Column {
        Text {
            text: "Hello World!"
            font.family: "Helvetica"
            font.pointSize: 24
            color: "red"
        }
        Text {
            text: "<b>Hello</b><i>World!</i>"
        }
    }
}
