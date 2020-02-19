import QtQuick 2.12
import QtQuick.Controls 2.12

Page {
    title: qsTr("Profile")

    Column {
        anchors.centerIn: parent
        spacing: 10
        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Profile")
        }
        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Edit")
            onClicked: stackView.push("EditProfile.qml")
        }
    }
}
