import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2 as StandartDialogs

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Image Viewer")

    header: ToolBar {
        ToolButton {
        id: menuButton
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        icon.source: "qrc:/images/drawer.png"
        onClicked: drawer.open()
        }
    }

    background: Rectangle {
        color: "darkGray"
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
                    triggered: () => fileOpenDialog.open()
                }
                ListElement {
                    text: qsTr("About...")
                    triggered: () => aboutDialog.open()
                }
            }
            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        asynchronous: true
    }

    StandartDialogs.FileDialog {
        id: fileOpenDialog
        title: "Select an image file"
        folder: shortcuts.documents
        nameFilters: [
            "Image files (.png *.jpeg *.jpg)"
        ]
        onAccepted: {
            image.source = fileOpenDialog.fileUrl
        }
    }

    Dialog {
        id: aboutDialog
        title: qsTr("About")
        modal: true
        anchors.centerIn: parent
        Label {
            anchors.fill: parent
            text: qsTr("Image Viewer\nBased on QML")
            horizontalAlignment: Text.AlignHCenter
        }
        standardButtons: Dialog.Ok
    }
}
