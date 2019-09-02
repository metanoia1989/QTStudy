import QtQuick 2.5
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2
import QtQuick.Extras 1.4

ApplicationWindow {
    visible: true
    width: 320
    height: 240
    title: qsTr("汽车时速表")

    Item {
        anchors.fill: parent
        CircularGauge {
            value: accelerating ? maximumValue : 0	// 判断是否加速
            anchors.centerIn: parent

            property bool accelerating: false

            Keys.onSpacePressed: accelerating = true
            Keys.onReleased: {
                if (event.key === Qt.Key_Space) {
                    accelerating = false;
                    event.accepted = true;
                }
            }

            Component.onCompleted: forceActiveFocus()

            Behavior on value {
                NumberAnimation {
                    duration: 1000
                }
            }
        }
    }
}
