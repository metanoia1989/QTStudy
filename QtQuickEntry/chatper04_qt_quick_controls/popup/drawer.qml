import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ApplicationWindow {
    id: window;  visible: true
    width: 300; height: 250
    title: qsTr("Hello World")
    background: Rectangle { color: "lightgreen" }

    Drawer {
        id: drawer
        width: 0.66 * window.width; height: window.height
        ColumnLayout {
            anchors.fill: parent
            CheckBox { text: qsTr("E-mail") }
            CheckBox { text: qsTr("Calendar") }
            CheckBox { text: qsTr("Contacts") }
        }
    }

    Label {
        id: content
        text: "Aa"; font.pixelSize: 96
        anchors.fill: parent
        verticalAlignment: Label.AlignVCenter
        horizontalAlignment: Label.AlignHCenter
        transform: Translate {
            x: drawer.position * content.width * 0.33
        }
    }
}
