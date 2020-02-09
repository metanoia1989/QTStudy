import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 250; height: 200

    Column {
        spacing: 20
        anchors.centerIn: parent

        RangeSlider {
            from: 0; to: 100; stepSize: 5
            first.value: 25; second.value: 75
        }

        RangeSlider {
            id: control; from: 0; to: 100
            first.value: 25; second.value: 75
            background: Rectangle {
                x: control.leftPadding
                y: control.topPadding + control.availableHeight / 2 - height / 2
                implicitWidth: 200; implicitHeight: 4
                width: control.availableWidth; height: implicitHeight
                radius: 2; color: "#bdbebf"
                Rectangle {
                    x: control.first.visualPosition * parent.width
                    width: control.second.visualPosition * parent.width - x
                    height: parent.height
                    color: "#21be2b"; radius: 2
                }
            }
            first.handle: Rectangle {
                x: control.leftPadding + control.first.visualPosition * (control.availableWidth - width)
                y: control.topPadding + control.availableHeight / 2 - height / 2
                implicitWidth: 26; implicitHeight: 26; radius: 13
                color: control.first.pressed ? "#000000" : "#f6f6f6"
                border.color: "#bdbebf"
            }
            second.handle: Rectangle {
                x: control.leftPadding + control.second.visualPosition * (control.availableWidth - width)
                y: control.topPadding + control.availableHeight / 2 - height / 2
                implicitWidth: 26; implicitHeight: 26; radius: 13
                color: control.second.pressed ? "#000000" : "#f6f6f6"
                border.color: "#bdbebf"
            }
        }
    }
}
