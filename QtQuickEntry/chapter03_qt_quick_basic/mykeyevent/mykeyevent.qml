import QtQuick 2.12

Item {
    width: 640; height: 480
    focus: true
    Keys.onPressed: {
        if (event.key === Qt.Key_Left) {
            console.log("move left")
            event.accepted = true
        }
    }
    Keys.onReturnPressed: console.log("Pressed return")
}
