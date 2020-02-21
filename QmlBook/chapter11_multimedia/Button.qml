

// M1>>
import QtQuick 2.5

Rectangle {
    id: root
    width: 196
    height: 64

    property alias text: caption.text

    signal clicked

    radius: 2

    color: mouseArea.pressed?"#1f1f1f":"#333333"
    border.color: "#999"
    border.width: 1

    Text {
        id: caption
        anchors.centerIn: parent
        font.pixelSize: 24
        color: "#ececec"
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        onClicked: root.clicked();
    }
}
// <<M1
