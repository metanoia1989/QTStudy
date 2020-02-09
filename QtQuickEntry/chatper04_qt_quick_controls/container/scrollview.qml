import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 200; height: 200

    ScrollView {
        anchors.fill: parent; clip: true
        Label { text: "ABC"; font.pixelSize: 224 }
    }
}
