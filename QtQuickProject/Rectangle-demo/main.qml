import QtQuick 2.4
import QtQuick.Window 2.3

Window {
    visible: true
    width: 250
    height: 250
    title: qsTr("Rectangle 矩形元素")
    MainForm {
        anchors.fill: parent
        mouseArea.onClicked: {
            topRect.visible = !topRect.visible // 控制矩形对象的可见性
        }
    }
}
