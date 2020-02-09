import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: window; width: 400; height: 400; visible: true

    Button {
        text: "Open";
        onClicked: dialog.open()
    }
    Dialog {
        id: dialog; title: "Dialog"
        x: 100; y: 100; width: 200; height: 200
        standardButtons: Dialog.Ok | Dialog.Cancel
        modal: true; focus: true
        onAccepted: console.log("Ok clicked")
        onRejected: console.log("Cancel clicked")
    }
}
