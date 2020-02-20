import QtQuick 2.12
import "../common"

Background {
    width: 240
    height: 300

    ListView {
        id: view
        anchors.fill: parent
        anchors.margins: 20
        currentIndex: 0
        clip: true
        model: 100
        delegate: numberDelegate
        spacing: 4
        highlight: highlightComponent
        highlightFollowsCurrentItem: false
        focus: true
    }

    Component {
        id: highlightComponent

        Item {
            width: ListView.view.width
            height: ListView.view.currentItem.height
            y: ListView.view.currentItem.y

            Behavior on y {
                SequentialAnimation {
                    PropertyAnimation {
                        target: highlightRectangle
                        property: "opacity"
                        to: 0
                        duration: 200
                    }
                    NumberAnimation { duration: 1 }
                    PropertyAnimation {
                        target: highlightRectangle
                        property: "opacity"
                        to: 1
                        duration: 200
                    }
                }
            }

            GreenBox {
                id: highlightRectangle
                anchors.fill: parent
            }
        }

    }

    Component {
        id: numberDelegate

        Item {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 40; height: 40

            Text {
                anchors.centerIn: parent
                font.pixelSize: 14
                text: index
            }
        }
    }
}
