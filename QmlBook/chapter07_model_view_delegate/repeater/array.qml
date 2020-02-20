import QtQuick 2.12
import "../common"

Column {
    spacing: 2

    Repeater {
        model: ["Enterprise", "Columbia", "Challenger", "Discovery", "Endeavour", "Atlantis"]
        BlueBox {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - 10; height: 32
            text: "%1(%2)".arg(modelData).arg(index)
        }
    }
}
