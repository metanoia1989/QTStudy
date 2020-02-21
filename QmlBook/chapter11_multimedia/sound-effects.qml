import QtQuick 2.12
import QtMultimedia 5.12

Item {
    id: window
    width: 1024
    height: 600

    states: State {
        name: "upsidedown"
        PropertyChanges { target: button; rotation: 180; }
    }

    transitions: [
        Transition {
            ParallelAnimation {
                ScriptAction { script: swosh.play() }
                PropertyAnimation { properties: "rotation"; duration: 200 }
            }
        }
    ]

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (window.state === "upsidedown") {
                window.state = "";
            } else {
                window.state = "upsidedown";
            }
        }
    }

    SoundEffect { id: beep; source: "beep.wav" }
    SoundEffect { id: swosh; source: "swosh.wav" }

    Rectangle {
        id: button
        anchors.centerIn: parent
        width: 200
        height: 200
        color: "red"

        MouseArea {
            anchors.fill: parent
            onClicked: beep.play()
        }
    }

}
