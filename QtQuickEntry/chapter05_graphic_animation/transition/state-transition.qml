import QtQuick 2.12

Item {
    width: 100; height: 100

    Rectangle {
        id: button
        width: 75; height: 75;
        anchors.centerIn: parent
        state: "RELEASED"

        MouseArea {
            anchors.fill: parent
            onPressed: button.state = "PRESSED"
            onReleased: button.state = "RELEASED"
        }

        states: [
            State {
                name: "PRESSED"
                PropertyChanges { target: button; color: "lightblue" }
            },
            State {
                name: "RELEASED"
                PropertyChanges { target: button; color: "lightsteelblue" }
            }
        ]

//        transitions: [
//            Transition {
//                from: "PRESSED"
//                to: "RELEASED"
//                ColorAnimation { target: button; duration: 100 }
//            },
//            Transition {
//                from: "RELEASED"
//                to: "PRESSED"
//                ColorAnimation { target: button; duration: 100 }
//            }
//        ]
        transitions: Transition {
            to: "*"
            ColorAnimation { target: button; duration: 100 }
        }
    }
}
