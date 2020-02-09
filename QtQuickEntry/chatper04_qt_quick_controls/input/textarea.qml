import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 250; height: 100

    ScrollView {
        anchors.fill: parent

        TextArea {
            text: "TextArea\n..\n..\n..\n..\n..\n..\n..\n..\n..\n..\n..\n.."
        }
    }
}
