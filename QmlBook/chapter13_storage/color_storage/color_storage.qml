import QtQuick 2.12
import Qt.labs.settings 1.1

Rectangle {
    id: root
    width: 320
    height: 240
    color: "#fff"
    Settings {
        id: settings
        property alias color: root.color
    }
    Settings {
        category: "root"
        property alias x: root.x
        property alias y: root.y
        property alias width: root.width
        property alias height: root.height
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.color = Qt.hsla(Math.random(), 0.5, 0.5, 1.0);
        }
    }
    function storeSettings() {
        settings.color = root.color;
    }
}
