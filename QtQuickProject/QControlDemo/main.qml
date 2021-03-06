import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2	// Qt Quick 对话框库

/* 对象声明 */
ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Qt Quick Controls 示例")

    menuBar: MenuBar {	// 菜单栏
        Menu {	// 菜单
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    MainForm {	// 主窗体
        anchors.fill: parent
        button1.onClicked: messageDialog.show(" Button 1 pressed")
        button2.onClicked: messageDialog.show("Button 2 pressed")
    }

    MessageDialog {
        id: messageDialog
        title: "May I have your attention, please?"

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
}
