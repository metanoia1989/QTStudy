import QtQuick 2.12
import QtMultimedia 5.12
import QtGraphicalEffects 1.12

Item {
    width: 600; height: 220

    Video {
        id: video; y: 10; width: 280; height: 200
        source: "video.wmv"
        MouseArea {
            anchors.fill: parent
            onClicked: video.play()
        }
    }

    FastBlur {
        x: 300; y: 10; width: 280; height: 200
        source: video; radius: 32
    }
}
