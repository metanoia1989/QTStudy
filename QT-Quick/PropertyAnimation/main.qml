import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("PropertyAnimation")
    MainForm {
        anchors.fill: parent
        mouseArea.onClicked: {
            /* 将鼠标单击位置的 x, y 坐标设为矩形Rect4的新坐标 */
            rect4.x = mouseArea.mouseX;
            rect4.y = mouseArea.mouseY;
        }
    }
}
