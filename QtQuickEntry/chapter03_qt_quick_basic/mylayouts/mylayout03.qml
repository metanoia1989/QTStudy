import QtQuick 2.2

Rectangle {
    LayoutMirroring.enabled: true
    LayoutMirroring.childrenInherit: true
    width: 300; height: 50
    color: "yellow"
    border.width: 1
    Row {
        anchors { left: parent.left; margins: 5 }
        y: 5; spacing: 5
        Repeater {
            model: 5
            Rectangle {
                color: "red"; width: 40; height: 40
                opacity: (5 - index) / 5
                Text { 
                    text: index + 1
                    anchors.centerIn: parent
                }
            }
        }
    }
}