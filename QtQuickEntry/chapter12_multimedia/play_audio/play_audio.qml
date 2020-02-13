import QtQuick 2.12
import QtQuick.Window 2.12
import QtMultimedia 5.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Audio {
        id: playMusic;
        source: "music.mp3"
        autoPlay: true
    }
}
