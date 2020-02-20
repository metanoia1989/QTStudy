import QtQuick 2.12
import "../common"

Background {
    width: 80
    height: 300

    ListView {
        anchors.rightMargin: 20
        anchors.bottomMargin: 32
        anchors.leftMargin: 20
        anchors.topMargin: 8
        anchors.fill: parent
        anchors.margins: 20
        clip: false; model: 100
        delegate: numberDelegate
        spacing: 5
    }

    Component {
        id: numberDelegate
        GreenBox {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 40; height: 40
            text: index
        }
    }
}
