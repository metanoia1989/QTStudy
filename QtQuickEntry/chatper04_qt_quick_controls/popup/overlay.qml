import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: window; width: 400; height: 400; visible: true

    Button { 
        text: "Open"; onClicked: popup.open() 
        Popup {
            id: popup
            parent: Overlay.overlay
            x: Math.round((parent.width - width)/2 )
            y: Math.round((parent.height - height)/2 )
            width: 100; height: 100
        }
    }

}
