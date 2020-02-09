import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 250; height: 200

    Column {
        spacing: 20
        anchors.centerIn: parent

        SpinBox {
            value: 50; editable: true
        }

        SpinBox {
            id: control
            value: 50; editable: true
            contentItem: TextInput {
                z: 2
                text: control.textFromValue(control.value, control.locale)
                font: control.font; color: "#21be2b"
                selectionColor: "#21be2b"; selectedTextColor: "#ffffff"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                readOnly: !control.editable
                validator: control.validator
                inputMethodHints: Qt.ImhFormattedNumbersOnly
            }
            up.indicator: Rectangle {
                x: control.mirrored ? 0 : parent.width - width
                height: parent.height
                implicitWidth: 40; implicitHeight: 40
                color: control.up.pressed ? "#e4e4e4" : "#f6f6f6"
                border.color: enabled ? "#21be2b" : "#bdbebf"
                Text {
                    text: "+"
                    font.pixelSize: control.font.pixelSize * 2
                    color: "#21be2b"; anchors.fill: parent; fontSizeMode: Text.Fit
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            down.indicator: Rectangle {
                x: control.mirrored ?  parent.width - width :0
                height: parent.height
                implicitWidth: 40; implicitHeight: 40
                color: control.up.pressed ? "#e4e4e4" : "#f6f6f6"
                border.color: enabled ? "#21be2b" : "#bdbebf"
                Text {
                    text: "-"
                    font.pixelSize: control.font.pixelSize * 2
                    color: "#21be2b"; anchors.fill: parent; fontSizeMode: Text.Fit
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

            }
            background: Rectangle {
                implicitWidth: 140; border.color: "#bdbebf"
            }
        }
    }
}
