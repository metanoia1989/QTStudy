import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 400; height: 200

    Row {
        spacing: 20
        anchors.centerIn: parent

        Dial {
            value: 40; from: 0; to: 100
        }

        Dial {
            id: control
            value: 40; from: 0; to: 100
            background: Rectangle {
                x: control.width / 2 - width /2;
                y: control.height / 2 - height /2;
                width: Math.max(64, Math.min(control.width, control.height))
                height: width; color: "transparent"; radius: width / 2
                border.color: control.pressed ? "#17a81a" : "#21be2b"
                opacity: control.enabled ? 1 : 0.3
            }
            handle: Rectangle {
                id: handleItem
                x: control.background.x + control.background.width / 2 - width / 2
                y: control.background.y + control.background.height / 2 - height / 2
                width: 16; height:16
                color: control.pressed ? "#17a81a" : "#21be2b"
                radius: 8; antialiasing: true
                opacity: control.enabled ? 1 : 0.3
                transform: [
                    Translate {
                        y: -Math.min(control.background.width, control.background.height) * 0.4 + handleItem.height / 2
                    },
                    Rotation {
                        angle: control.angle
                        origin.x: handleItem.width / 2; origin.y: handleItem.height / 2
                    }

                ]
            }
        }
    }
}
