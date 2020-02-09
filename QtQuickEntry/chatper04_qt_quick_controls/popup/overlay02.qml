import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: window; width: 400; height: 400; visible: true

    Column {
        Button {
            text: "打开modal弹出层"
            onClicked: popup.open()
            Popup {
                id: popup;
                width: 200; height: 200
                modal: true;
                Overlay.modal: Rectangle {
                    color: "yellow"
                }
            }
        }

        Button {
            text: "打开modaless弹出层"
            onClicked: popup02.open()
            Popup {
                id: popup02;
                width: 200; height: 200
                dim: true;
                Overlay.modeless: Rectangle {
                    color: "red"
                }
            }
        }
    }


}
