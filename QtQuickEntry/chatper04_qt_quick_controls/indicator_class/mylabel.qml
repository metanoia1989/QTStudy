import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 250; height: 200

    Column {
        spacing: 20
        anchors.centerIn: parent
        Label {
            text: qsTr("General Label")
            font.pixelSize: 22
            font.italic: true
        }
        Label {
            text: qsTr("Styled Label")
            color: "#21be2b"
            font.pointSize: 20
            topInset: -2
            leftInset: -2
            rightInset: -6
            bottomInset: -6
            background: Rectangle {
                color: "lightgrey"
            }
        }
    }
}
