import QtQuick 2.0

Rectangle {
    width: 80
    height: 80
    ColorAnimation on color {
        from: "blue"
        to: "aqua"
        duration: 1000
        loops: Animation.Infinite
    }
    RotationAnimation on rotation {
        from: 0
        to: 360
        duration: 1000
        direction: RotationAnimation.Clockwise
        loops: Animation.Infinite
    }
    NumberAnimation on radius {
        from: 0
        to: 40
        duration: 1000
        loops: Animation.Infinite
    }
    PropertyAnimation on x {
        from: 50
        to: 500
        duration: 1000
        loops: Animation.Infinite
        easing.type: Easing.InOutQuad
    }
}
