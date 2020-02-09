import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 200; height: 200

    ScrollView {
        id: control; width: 200; height: 200; focus: true

        Label { text: "ABC"; font.pixelSize: 224 }

        ScrollBar.vertical: ScrollBar {
            parent: control
            x: control.mirrored ? 0 :control.width - width
            y: control.topPadding
            height: control.ScrollBar.horizontal.active
        }
        ScrollBar.horizontal: ScrollBar {
            parent: control
            x: control.leftPadding
            y: control.height - height
            width: control.availableWidth
            active: control.ScrollBar.vertical.active
        }
        background: Rectangle {
            border.color: control.activeFocus ? "#21be2b" : "#bdbebf"
        }
    }
}
