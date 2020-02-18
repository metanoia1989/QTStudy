import QtQuick 2.12

Rectangle {
    id: root
    width: 120; height: 240
    color: "#4a4a4a"
    Image {
        id: triangle
        x: (parent.width-width)/2; y: 40
        source: "assets/triangle_red.png"
    }
    Text {
        y: triangle.y + triangle.height + 20
        width: root.width
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        text: "Triangle"
    }
}
