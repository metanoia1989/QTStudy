import QtQuick 2.12

Item {
    id: root
    width: background.width
    height: background.height

    Image {
        id: background
        source: "assets/background_medium.png"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            greenBox.y = blueBox.y = redBox.y = 205;
        }
    }

    ClickableImage {
        id: greenBox
        x: 40; y: root.height-height
        source: "assets/box_green.png"
        text: "animation on property"
        NumberAnimation on y {
            to: 40; duration: 4000
        }
    }

    ClickableImage {
        id: blueBox
        x: (root.width-width)/2; y: root.height-height
        source: "assets/box_blue.png"
        text: "behavior on property"
        Behavior on y {
            NumberAnimation { duration: 4000 }
        }
        onClicked: {
//            y = 40;
            y = 40+Math.random()*(250-40);
        }
    }

    ClickableImage {
        id: redBox
        x: root.width-width-40; y: root.height-height
        source: "assets/box_red.png"
        onClicked: anim.start()
        text: "standalone animation"

        NumberAnimation {
            id: anim
            target: redBox
            property: "y"
            duration: 4000
            to: 40
        }
    }
}
