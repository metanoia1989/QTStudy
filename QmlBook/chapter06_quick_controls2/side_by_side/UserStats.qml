import QtQuick 2.12
import QtQuick.Controls 2.12

Page {
    header: Label {
        text: qsTr("Your Stats")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Label {
        text: qsTr("User statistics")
        anchors.centerIn: parent
    }
}
