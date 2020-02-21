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

    Rectangle {
        id: progressBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 100
        height: 30
        color: "lightGray"

        Rectangle {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: player.duration > 0 ? parent.width * player.position / player.duration : 0
            color: "darkGray"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (player.seekable) {
                    player.seek(player.duration * mouse.x / width);
                }
            }
        }
    }

    Connections {
        target: player
        onMediaObjectChanged: {
            if (player.mediaObject) {
                player.mediaObject.notifyInterval = 50;
            }
        }
    }

    Component.onCompleted: {
        player.play();
        if (player.mediaObject) {
            player.mediaObject.notifyInterval = 50;
        }
    }
}
