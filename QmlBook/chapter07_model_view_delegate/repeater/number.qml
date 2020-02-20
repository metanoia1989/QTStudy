import QtQuick 2.12
import "../common"

Column {
    spacing: 2

    Repeater {
        model: 10
        BlueBox {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 120
            height: 32
            text: index
        }
    }
}
