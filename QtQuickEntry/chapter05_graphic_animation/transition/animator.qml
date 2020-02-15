import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640; height: 480

    Rectangle {
        id: mixBox
        width: 50; height: 50
        ParallelAnimation {
            ColorAnimation {
                target: mixBox
                property: "color"
                from: "forestgreen"
                to: "lightsteelblue"
                duration: 1000
            }
            ScaleAnimator {
                target: mixBox
                from: 2
                to: 1
                duration: 1000
            }
            running: true
        }
    }
}
