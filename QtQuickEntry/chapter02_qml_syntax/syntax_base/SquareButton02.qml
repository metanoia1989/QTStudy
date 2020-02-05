import QtQuick 2.0

Rectangle {
    id: root
    property bool pressed: mouseArea.pressed
    signal buttonClicked(real xPos, real yPos)
    width: 100; height: 100
    color: "red"
    function randomizeColor() {
        root.color = Qt.rgba(Math.random(), Math.random(), Math.random(), 1)
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: root.buttonClicked(mouse.x, mouse.y)
    }
}
