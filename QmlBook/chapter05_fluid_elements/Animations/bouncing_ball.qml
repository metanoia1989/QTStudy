import QtQuick 2.12

Item {
    id: root
    width: 640; height: 380
    property int duration: 3000

    Rectangle {
        id: sky
        width: parent.width
        height: 200
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#0080ff" }
            GradientStop { position: 1.0; color: "#66ccff" }
        }
    }
    Rectangle {
        id: ground
        anchors.top: sky.bottom
        anchors.bottom: root.bottom
        width: parent.width
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#00ff00" }
            GradientStop { position: 1.0; color: "#00803f" }
        }
    }
    Image {
        id: ball
        x: 0; y: root.height-height
        source: "assets/soccer_ball.png"
        width: 50; height: 50

        MouseArea {
            anchors.fill: parent
            onClicked: {
                ball.x = 0;
                ball.y = root.height-ball.height;
                ball.rotation = 0;
                anim.restart();
            }
        }
    }
    ParallelAnimation {
        id: anim
        SequentialAnimation {
            NumberAnimation {
                target: ball
                property: "y"
                duration: root.duration * 0.4
                easing.type: Easing.OutCirc
                to: 20
            }
            NumberAnimation {
                target: ball
                property: "y"
                duration: root.duration * 0.6
                easing.type: Easing.OutBounce
                to: root.height - ball.height
            }
        }
        NumberAnimation {
            target: ball
            property: "x"
            duration: root.duration
            to: root.width - ball.width
        }
        NumberAnimation {
            target: ball
            property: "x"
            duration: root.duration
            to: root.width - 100
        }
    }
}
