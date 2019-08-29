import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }
        Rect {
            x: 25; y:25
            opacity: (360.0 - x)/360
        }
    }

}
