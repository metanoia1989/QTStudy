import QtQuick 2.12
import QtQuick.Window 2.12
import "qrc:///../common"

Window {
    visible: true
    width: 320
    height: 320

    Background {
        anchors.fill: parent

        TableView {
            id: view
            anchors.fill: parent
            anchors.margins: 20
            rowSpacing: 5
            columnSpacing: 5
            clip: true
            model: tableModel
            delegate: cellDelegate
        }
    }

    Component {
        id: cellDelegate

        GreenBox {
            implicitHeight: 40
            implicitWidth: 40

            Text {
                anchors.centerIn: parent
                text: display
            }
        }
    }
}
