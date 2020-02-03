import QtQuick 2.4
import QtQuick.Window 2.3

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("你好 QtQuick")
    MainForm {
        anchors.fill: parent
        mouseArea.onClicked: {
            console.log(qsTr('点击背景. 文本是："' + textEdit.text + '"'))
        }
    }
}
