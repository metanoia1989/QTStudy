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
            id: vbar; hoverEnabled: true
            active: hovered || pressed
            orientation: Qt.Vertical
            size: frame.height / content.height
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
        }

        ScrollBar {
            id: hbar; hoverEnabled: true
            active: hovered || pressed
            orientation: Qt.Vertical
            size: frame.width / content.width
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
        }
    }
}
