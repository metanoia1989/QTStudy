import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 250; height: 200

    Column {
        spacing: 20
        anchors.centerIn: parent

        BusyIndicator {
            running: true
        }

        BusyIndicator {
            id: control
            contentItem: Item {
                implicitWidth: 64; implicitHeight: 64
                Item {
                    id: item;
                    width: 64; height: 64
                    x: parent.width / 2 - 32
                    y: parent.height / 2 - 32
                    opacity: control.running ? 1 : 0

                    Behavior on opacity {
                        OpacityAnimator { duration: 250 }
                    }
                    RotationAnimator {
                        target: item
                        running: control.visible && control.running
                        from: 0; to: 360
                        loops: Animation.Infinite; duration: 1250
                    }
                    Repeater {
                        id: repeater; model: 6
                        Rectangle {
                            x: item.width / 2 - width / 2
                            y: item.height / 2 - height / 2
                            implicitWidth: 10; implicitHeight: 10
                            radius: 5; color: "#21be2b"
                            transform: [
                                Translate {
                                    y: -Math.min(item.width, item.height) * 0.5 + 5
                                },
                                Rotation {
                                    angle: index / repeater.count * 360
                                    origin.x: 5; origin.y: 5
                                }

                            ]
                        }
                    }
                }
            }
        }
    }
}
