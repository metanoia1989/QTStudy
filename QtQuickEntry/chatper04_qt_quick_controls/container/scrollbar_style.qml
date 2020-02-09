import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 200; height: 200

    Rectangle {
        id: frame; clip: true; anchors.fill: parent

        Text {
            id: content; text: "ABC"
            font.pixelSize: 224
            x: -hbar.position * width
            y: -vbar.position * height
        }

        ScrollBar {
            id: vbar; active: true; orientation: Qt.Vertical
            size: frame.height / content.height
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            contentItem: Rectangle {
                implicitWidth: 6
                implicitHeight: 100
                radius: width / 2
                color: vbar.pressed ? "#81e889" : "#c2f4c6"
            }
        }

        ScrollBar {
            id: hbar;  active: true; orientation: Qt.Vertical
            size: frame.width / content.width
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
        }
    }
}
