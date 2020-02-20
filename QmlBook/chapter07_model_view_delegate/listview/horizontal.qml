import QtQuick 2.12
import "../common"

Background {
    width: 400
    height: 80

    ListView {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 4
        clip: true;
        model: 100
        orientation: ListView.Horizontal
        delegate: numberDelegate
    }

    Component {
        id: numberDelegate
        GreenBox {
            anchors.verticalCenter: parent.verticalCenter
            width: 40; height: 40
            text: index
        }
    }
}
