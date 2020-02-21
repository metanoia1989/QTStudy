import QtQuick 2.12
import QtMultimedia 5.12

Item {
    width: 1024
    height: 600

    MediaPlayer {
        id: player
        source: "tutorial.mp4"
    }

    VideoOutput {
        anchors.fill: parent
        source: player
    }

    Component.onCompleted: player.play();
}
