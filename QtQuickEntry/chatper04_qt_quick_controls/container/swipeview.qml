import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 250; height: 300

    SwipeView {
        id: view; currentIndex: 1; anchors.fill: parent
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

    PageIndicator {
        id: indicator
        count: view.count; currentIndex: view.currentIndex
        anchors.bottom: view.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
