import QtQuick 2.12

Item {
    width: 320; height: 480

    MouseArea {
        onClicked: anim.start();
        anchors.fill: parent
    }
    SequentialAnimation {
        id: anim
        ScriptAction { script: image.goalSprite = "falling"; }
        NumberAnimation {
            target: image; property: "y"
            to: 480; duration: 12000
        }
        ScriptAction {
            script: {
                image.goalSprite = "";
                image.jumpTo("still");
            }
        }
        PropertyAction {
            target: image; property: "y"; value: 0
        }
    }
    SpriteSequence {
        id: image; width: 256; height: 256
        anchors.horizontalCenter: parent.horizontalCenter
        interpolate: false; goalSprite: ""

        Sprite {
            name: "still"; source: "BearSheet.png"
            frameCount: 1; frameWidth: 256; frameHeight: 256
            frameDuration: 100
            to: { "still": 1, "blink": 0.1, "floating": 0 }
        }
        Sprite {
            name: "blink"; source: "BearSheet.png"
            frameCount: 3; frameWidth: 256; frameHeight: 256
            frameX: 256; frameY: 1536
            frameDuration: 100
            to: { "still": 1 }
        }
        Sprite {
            name: "floating"; source: "BearSheet.png"
            frameCount: 9; frameWidth: 256; frameHeight: 256
            frameX: 0; frameY: 0
            frameDuration: 160
            to: { "still": 0, "flailing": 1 }
        }
        Sprite {
            name: "flailing"; source: "BearSheet.png"
            frameCount: 8; frameWidth: 256; frameHeight: 256
            frameX: 0; frameY: 768
            frameDuration: 160
            to: { "flalling": 1 }
        }
        Sprite {
            name: "flalling"; source: "BearSheet.png"
            frameCount: 5; frameWidth: 256; frameHeight: 256
            frameY: 1280
            frameDuration: 160
            to: { "flalling": 1 }
        }
    }
}
