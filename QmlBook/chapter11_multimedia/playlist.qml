import QtQuick 2.12
import QtMultimedia 5.12

Rectangle {
    id: root
    width: 1024
    height: 600
    color: "black"

    MediaPlayer {
        id: player
        playlist: Playlist {
            PlaylistItem { source: "tutorial.mp4" }
            PlaylistItem { source: "tutorial.mp4" }
            PlaylistItem { source: "tutorial.mp4" }
        }
    }

    VideoOutput {
        anchors.fill: parent
        source: player
    }

    Component.onCompleted: {
        player.playlist.currentIndex = 0;
        player.play();
    }
}
