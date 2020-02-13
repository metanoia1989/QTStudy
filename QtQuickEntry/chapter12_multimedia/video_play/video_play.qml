import QtQuick 2.12
import QtMultimedia 5.12

Video {
    id: video; width: 800; height: 600
    source: "video.wmv"

    MouseArea {
        anchors.fill: parent
        onClicked: video.play()
    }

    focus: true
    Keys.onSelectPressed: video.playbackState === MediaPlayer.PlayingState
        ? video.pause() : video.play()
    Keys.onLeftPressed: video.seek(video.position - 5000)
    Keys.onRightPressed: video.seek(video.position + 5000)
}
