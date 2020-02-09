import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 250; height: 250

    Column {
        spacing: 20
        anchors.centerIn: parent

        PageIndicator {
            count: 5; currentIndex: 2
        }
        PageIndicator {
            id: control
            count: 5; currentIndex: 2
            interactive: true
            delegate: Rectangle {
                implicitWidth: 8; implicitHeight: 8
                color: "#21be2b"
                opacity: index === control.currentIndex ? 0.95 : pressed ? 0.7 : 0.45
                Behavior on opacity {
                    OpacityAnimator { duration: 100 }
                }
            }
        }
    }
}
