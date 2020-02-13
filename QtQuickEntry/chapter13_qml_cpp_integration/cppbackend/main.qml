import QtQuick 2.12
import QtQuick.Controls 2.12
import io.qt.examples.backend 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    BackEnd {
        id: backend
        onUserNameChanged: console.log(backend.userName)
    }

    Column {
        spacing: 10
        anchors.centerIn: parent

        TextField {
            placeholderText: qsTr("User name")
            onTextChanged: backend.userName = text
        }

        Label {
            text: backend.userName
            width: 200; font.pointSize: 20
            background: Rectangle {
                color: "lightgrey"
            }
        }
    }
}
