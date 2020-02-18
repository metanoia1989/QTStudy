import QtQuick 2.12

BrightSquare {
    id: root
    width: 600; height: 400
    property int duration: 3000
    property Item ufo: ufo

    Image {
        anchors.fill: parent
        source: "assets/ufo_background.png"
    }

    ClickableImageV3 {
        id: ufo
        x: 20; y: root.height-height
        text: "ufo"
        source: "assets/ufo.png"
        onClicked: anim.restart()
    }

    SequentialAnimation {
        id: anim

        NumberAnimation {
            target: ufo
            property: "y"
            duration: root.duration * 0.6
            to: 20
        }
        NumberAnimation {
            target: ufo
            property: "x"
            duration: root.duration * 0.4
            to: 400
        }
    }
}
