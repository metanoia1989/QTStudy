import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2 as StandardDialogs

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Image Viewer")

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Open...")
                onTriggered: fileOpenDialog.open()
            }
        }
        Menu {
            title: qsTr("&Help")
            MenuItem {
                text: qsTr("&About...")
                onTriggered: aboutDialog.open()
            }
        }
    }

    header: ToolBar {
        Flow {
            anchors.fill: parent
            ToolButton {
                text: qsTr("Open")
                icon.source: "qrc:/images/open.png"
                onClicked: fileOpenDialog.open()
            }
        }
    }

    background: Rectangle {
        color: "darkGray"
    }

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        asynchronous: true
    }

    StandardDialogs.FileDialog {
        id: fileOpenDialog
        title: "Select an image file"
        folder: shortcuts.documents
        nameFilters: [
            "Image files (*.png *.jpeg *.jpg)"
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
