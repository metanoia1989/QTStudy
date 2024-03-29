import QtQuick 2.12
import QtMultimedia 5.12
import QtGraphicalEffects 1.12

Item {
    width: 300; height: 300

    Video {
        id: video; width: 300; height: 300
        source: "video.wmv"
        fillMode: VideoOutput.Stretch
        visible: false
    }

    MouseArea {
        anchors.fill: parent
        onClicked: video.play()
    }

    Image {
        id: mask
        source: "mask.png"
        sourceSize: Qt.size(parent.width, parent.height)
        smooth: true; visible: false
    }

    ThresholdMask {
        anchors.fill: parent
        source: video; maskSource: mask
        threshold: 0.45; spread: 0.2
    }
}
