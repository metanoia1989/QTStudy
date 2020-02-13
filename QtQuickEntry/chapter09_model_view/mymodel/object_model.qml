import QtQuick 2.12
import QtQml.Models 2.12

Rectangle {
    ObjectModel {
        id: itemModel
        Rectangle { height: 30; width: 100; radius: 5; color: "red" }
        Rectangle { height: 30; width: 80;  color: "lightgrey" }
        Rectangle { height: 30; width: 150; radius: 10; color: "blue" }
        Rectangle { height: 30; width: 60; border.width: 3; color: "yellow" }
    }

    ListView {
        anchors.fill: parent; anchors.margins: 5
        model: itemModel
        spacing: 4
    }
}
