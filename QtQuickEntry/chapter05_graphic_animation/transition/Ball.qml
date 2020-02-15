import QtQuick 2.12

Rectangle {
    id: ball
    width: 75; height: 75; radius: width
    color: "lightsteelblue"

    Behavior on x {
        NumberAnimation {
            id: bouncebehavior
            easing {
                type: Easing.OutElastic
                amplitude: 1.0
                period: 0.5
            }
            duration: 700
        }
    }
    Behavior on y {
        animation: bouncebehavior
    }
    Behavior {
        ColorAnimation { target: ball; duration: 300 }
    }
}
