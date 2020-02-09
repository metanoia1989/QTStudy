import QtQuick 2.12
import QtQuick.Controls 2.12

ImageViewWindow {
    id: window
    width: 640; height: 480

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Open...")
                onTriggered: openFileDialog()
            }
        }
        Menu {
            title: qsTr("&Help")
            MenuItem {
                text: qsTr("&About...")
                onTriggered: openAboutDialog()
            }
        }
    }

    header: ToolBar {
        Flow {
            anchors.fill: parent
            ToolButton {
                text: qsTr("Open")
                icon.source: "qrc:/images/open.png"
                onClicked: openFileDialog()
            }
        }
    }

}
