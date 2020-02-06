import QtQuick 2.12
import QtQuick.Window 2.12

Rectangle {
    width: 640; height: 480
    color: "green"
    MouseArea {
        anchors.fill: parent
        onClicked: { parent.color = "red" } 
    }
}
