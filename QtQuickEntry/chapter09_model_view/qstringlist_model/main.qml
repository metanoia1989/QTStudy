import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ListView {
        anchors.fill: parent
        model: stringListModel
        delegate: Rectangle {
            height: 25; width: 100
            Text { text: modelData }
        }
    }
}
