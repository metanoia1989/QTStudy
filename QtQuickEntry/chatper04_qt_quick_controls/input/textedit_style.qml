import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 250; height: 200

    Column {
        spacing: 20
        anchors.centerIn: parent

        TextField {
            y: 10; width: 200
            placeholderText: qsTr("Please enter a password")
            echoMode: TextInput.PasswordEchoOnEdit
            validator: IntValidator { bottom: 11; top: 20 }
            onAccepted: console.debug(text)
        }

        TextField {
            id: control
            placeholderText: qsTr("Enter description")
            background: Rectangle {
                implicitWidth: 200; implicitHeight: 40
                color: control.enabled ? "transparent" : "#353637"
                border.color: control.enabled ? "#21be2b" : "transparent"
            }
        }
    }
}
