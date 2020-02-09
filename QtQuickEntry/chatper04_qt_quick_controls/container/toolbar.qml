import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ApplicationWindow {
    visible: true
    width: 250; height: 300

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton { text: qsTr("<"); onClicked: stack.pop() }
            Label {
                text: "Title"; elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            ToolButton {
                id: helpButton; text: qsTr(":")
                onClicked: menu.open()
                Menu {
                    id: menu; y: helpButton.height
                    MenuItem { text: "Help..." }
                    MenuItem { text: "About" }
                }
            }
        }
    }

    StackLayout {
        id: stack; anchors.fill: parent;
    }
}
