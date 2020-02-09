import QtQuick 2.12
import QtQuick.Controls 2.12

ImageViewWindow {
    id: window
    width: 360; height: 520

    header: ToolBar {
        ToolButton {
        id: menuButton
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        icon.source: "qrc:/images/drawer.png"
        onClicked: drawer.open()
        }
    }

    Drawer {
        id: drawer
        width: Math.min(window.width, window.height) / 3 * 2
        height: window.height

        ListView {
            focus: true
            currentIndex: -1
            anchors.fill: parent
            delegate: ItemDelegate {
                width: parent.width
                text: model.text
                highlighted: ListView.isCurrentItem
                onClicked: {
                    drawer.close()
                    model.triggered()
                }
            }
            model: ListModel {
                ListElement {
                    text: qsTr("Open...")
                    triggered: () => openFileDialog()
                }
                ListElement {
                    text: qsTr("About...")
                    triggered: () => openAboutDialog()
                }
            }
            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }

}
