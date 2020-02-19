import QtQuick 2.12
import QtQuick.Controls 2.12
import Qt.labs.platform 1.0 as NativeDialogs

ApplicationWindow {
    id: root
    visible: true
    width: 640; height: 480
    title: (_fileName.length === 0 ? qsTr("Document") : _fileName) + (_isDirty ? "*" : "")
    property bool _isDirty: true	// 文档是否有未保存的改变
    property string _fileName	// 文档的文件名
    property bool _tryingToClose: false	// 是否尝试关闭窗口

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&New")
                icon.name: "document-new"
                onTriggered: root.newDocument()
            }
            MenuSeparator { }
            MenuItem {
                text: qsTr("&Open")
                icon.name: "document-open"
                onTriggered: openDocument()
            }
            MenuItem {
                text: qsTr("&Save")
                icon.name: "document-save"
                onTriggered: saveDocument()
            }
            MenuItem {
                text: qsTr("Save &As...")
                icon.name: "document-save-as"
                onTriggered: saveAsDocument()
            }
        }
    }

    onClosing: {
        if (root._isDirty) {
            closeWarningAsDialog.open();
            close.accepted = false;
        }
    }

    NativeDialogs.FileDialog {
        id: openDialog
        title: "Open"
        folder: NativeDialogs.StandardPaths.writableLocation(
                    NativeDialogs.StandardPaths.DocumentsLocation)
        onAccepted: {
            let window = root._createNewDocument();
            window._fileName = openDialog.file;
            window.show();
        }
    }
    NativeDialogs.FileDialog {
        id: saveAsDialog
        title: "Save As"
        folder: NativeDialogs.StandardPaths.writableLocation(
                    NativeDialogs.StandardPaths.DocumentsLocation)
        onAccepted: {
            root._fileName = saveAsDialog.file;
            saveDocument();
        }
        onRejected: {
            root._tryingToClose = false;
        }
    }
    NativeDialogs.MessageDialog {
        id: closeWarningAsDialog
        title: "Closing document"
        text: "You have unsaved changed. Do you want to save your changed?"
        buttons: NativeDialogs.MessageDialog.Yes | NativeDialogs.MessageDialog.No
            | NativeDialogs.MessageDialog.Cancel
        onYesClicked: {
            root._tryingToClose = true;
            root.saveDocument();
        }
        onNoClicked: {
            root._isDirty = false;
            root.close();
        }
        onRejected: {
        }
    }

    function _createNewDocument() {
        let component = Qt.createComponent("DocumentWindow.qml")
        let window = component.createObject();
        return window;
    }

    function newDocument() {
        let window = _createNewDocument();
        window.show();
    }

    function openDocument() {
        openDialog.open();
    }

    function saveAsDocument() {
        saveAsDialog.open();
    }

    function saveDocument() {
        if (_fileName.length === 0) {
            root.saveAsDocument();
        } else {
            console.log("Saving document");
            root._isDirty = false;

            if (root._tryingToClose) {
                root.close();
            }
        }
    }
}
