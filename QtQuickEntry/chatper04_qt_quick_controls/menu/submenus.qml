import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 600; height: 400

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {
            if (mouse.button === Qt.RightButton) {
                contextMenu.popup()
            }
        }
        onPressAndHold: {
            if (mouse.source === Qt.MouseEventNotSynthesized) {
                contextMenu.popup()
            }
        }

        Menu {
            id: contextMenu
            Action { text: "Cut" }
            Action { text: "Copy" }
            Action { text: "Paste" }
            MenuSeparator { }
            Menu {
                title: "Find/Replace"
                Action { text: "Find Next" }
                Action { text: "Find Previous" }
                Action { text: "Find Replace" }
            }
        }
    }
}
