import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: window; width: 400; height: 400; visible: true

    Button { text: "Open"; onClicked: popup.open() }

    Popup {
        id: popup
        x: Math.round((parent.width - width)/2)
        y: Math.round((parent.height - height)/2)
        width: 100; height: 100
        modal: true; focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        onAboutToHide: console.log("Popup is about to hide.")
        onAboutToShow: console.log("Popup is about to open.")
        enter: Transition {
            NumberAnimation { property: "opacity"; from: 0.0; to: 1.0 }
        }
        exit: Transition {
            NumberAnimation { property: "opacity"; from: 1.0; to: 0.0 }
        }
    }
}
