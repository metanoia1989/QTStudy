import QtQuick 2.5
import QtQuick.Controls 1.5

ApplicationWindow {
    visible: true
    width: 320
    height: 270
    title: qsTr("温度计")

    MainForm {
        anchors.fill: parent
        button1.onClicked: thermometer.value += 5
        button2.onClicked: thermometer.value -= 5
    }
}
