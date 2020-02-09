import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 400; height: 400
    title: qsTr("ScrollBar")

    Flickable {
        id: flickable; clip: true

        contentWidth: parent.width * 2
        contentHeight: parent.height * 2

        ScrollBar.vertical: ScrollBar {
            id: scrollBar
            parent: flickable.parent
            anchors.top: flickable.top
            anchors.left: flickable.left
            anchors.bottom: flickable.bottom
        }

        Keys.onUpPressed: scrollBar.decrease()
        Keys.onDownPressed: scrollBar.increase()

        Column {
            anchors.fill: parent
            Text { text: "Hello QML!"; font.pointSize: 20 }
            Text { text: "Hello QML!"; font.pointSize: 20 }
            Text { text: "Hello QML!"; font.pointSize: 20 }
            Text { text: "Hello QML!"; font.pointSize: 20 }
            Text { text: "Hello QML!"; font.pointSize: 20 }
            Text { text: "Hello QML!"; font.pointSize: 20 }
            Text { text: "Hello QML!"; font.pointSize: 20 }
            Text { text: "Hello QML!"; font.pointSize: 20 }
            Text { text: "Hello QML!"; font.pointSize: 20 }
            Text { text: "Hello QML!"; font.pointSize: 20 }
            Text { text: "Hello QML!"; font.pointSize: 20 }
            Text { text: "Hello QML!"; font.pointSize: 20 }
        }
    }
}
