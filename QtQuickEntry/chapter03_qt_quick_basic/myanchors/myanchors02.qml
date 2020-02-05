import QtQuick 2.2

Item {
    Rectangle {
        id: rect1
        x: 0; 
        width: 50; height: 50; color: "blue"
    }
    Rectangle {
        id: rect2
        width: 50; height: 50; color: "red"
        anchors.left: rect1.right
        anchors.right: rect3.left
    }
    Rectangle {
        id: rect3
        x: 150
        width: 50; height: 50; color: "yellow"
        // anchors.left: rect2.right
        // anchors.top: rect2.bottom
    }
}