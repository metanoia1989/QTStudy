import QtQuick 2.12

Item {
    width: 150; height: 100

    Rectangle {
        id: signal;
        anchors.fill: parent;
        color: "lightgrey"
        state: "WARNING"

        Image {
            id: img;
            anchors.centerIn: parent;
            source: "warning.png"
        }

        states: [
            State {
                name: "WARNING"
                PropertyChanges { target: signal; color: "lightgrey"  }
                PropertyChanges { target: img; source: "warning.png"  }
            },
            State {
                name: "CRITICAL"
                PropertyChanges { target: signal; color: "red"  }
                PropertyChanges { target: img; source: "critical.png"  }
            }
        ]
    }

    Image {
        id: signalswitch
        width: 22; height: 22
        source: "switch.png"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (signal.state === "WARNING") {
                    signal.state = "CRITICAL";
                } else {
                    signal.state = "WARNING";
                }
            }
        }
    }
}
