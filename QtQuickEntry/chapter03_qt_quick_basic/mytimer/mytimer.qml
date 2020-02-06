import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Text {
        id: time
        anchors.centerIn: parent
        font.pointSize: 20
    }
    Timer {
        interval:500; running: true; repeat: true;
        onTriggered: time.text = Date().toLocaleString("zh-CN")
    }
}
