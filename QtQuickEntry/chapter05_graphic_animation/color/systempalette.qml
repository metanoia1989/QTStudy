import QtQuick 2.12

Rectangle {
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }

    width: 640; height: 480
    color: myPalette.window

    Text {
        anchors.centerIn: parent
        text: qsTr("你好你好")
        color: myPalette.windowText
    }
}
