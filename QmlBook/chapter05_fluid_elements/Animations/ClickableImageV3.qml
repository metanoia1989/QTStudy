import QtQuick 2.5

Item {
    id: root
    width: container.childrenRect.width + 16
    height: container.childrenRect.height + 16
    property alias text: label.text
    property alias source: image.source
    signal clicked

    property bool framed: false

    Rectangle {
        anchors.fill: parent
        color: "white"
        visible: root.framed
    }

    Column {
        id: container
        x: 8; y: 8
        Image { id: image }
        Text {
            id: label
            width: image.width
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
            color: "#e0e0e0"
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
