import QtQuick 2.12

Rectangle {
    color: "lightgrey"
    width: 100; height: 100

    Rectangle {
        color: "blue"
        width: 25; height: 25
    }
    Rectangle {
        color: "yellow"
        x: 25; y: 25
        width: 25; height: 25
        scale: 1.6
        transformOrigin: "TopLeft"
    }
}
