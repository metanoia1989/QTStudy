import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ApplicationWindow {
    visible: true
    width: 250; height: 300

    header: TabBar {
        id: bar; width: parent.width
        TabButton { text: qsTr("Red") }
        TabButton { text: qsTr("Yellow") }
        TabButton { text: qsTr("Blue") }
    }

    StackLayout {
        anchors.fill: parent; currentIndex: bar.currentIndex
        Item {
            Rectangle { anchors.fill: parent; color: "red" }
        }
        Item {
            Rectangle { anchors.fill: parent; color: "yellow" }
        }
        Item {
            Rectangle { anchors.fill: parent; color: "blue" }
        }
    }
}
