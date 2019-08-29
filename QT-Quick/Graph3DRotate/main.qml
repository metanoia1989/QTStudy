import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("3D旋转")
    MyGraph {
        anchors.fill: parent
    }
}
