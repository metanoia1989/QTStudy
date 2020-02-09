import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 250; height:200

    Column {
        spacing: 20
        anchors.centerIn: parent

        Switch { text: qsTr("Default Switch") }

        Switch {
            id: control
            text: qsTr("Styled Switch")
            checked: true
            indicator: Rectangle {
                implicitWidth: 48; implicitHeight: 26
                x: control.leftPadding; y: parent.height /2 - height / 2
                radius: 13;
                color: control.checked ? "#17a81a" : "#ffffff"
                border.color: control.checked ? "#17a81a" : "#cccccc"
                Rectangle {
                    x: control.checked ? parent.width - width : 0
                    width: 26; height: 26
                    radius: 13
                    color: control.down ? "#cccccc" : "#ffffff"
                    border.color: control.checked ? (control.down ? "#17a81a" : "#21be2b") : "#999999"
                }
            }
            contentItem: Text {
                text: control.text; font: control.font
                opacity: enabled ? 1.0 : 0.3
                color: control.down ? "#17a81a" : "#21be2b"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                leftPadding: control.indicator.width + control.spacing
            }
        }
    }
}
