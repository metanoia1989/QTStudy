import QtQuick 2.0

Item {
    width: 600; height: 600

    Rectangle {
        width: 10; height: width * 2
        color: "red"; focus: true
        anchors.centerIn: parent
        Keys.onSpacePressed: height = Qt.binding(() => width * 20)

        MouseArea {
            anchors.fill: parent
            onClicked:  parent.width += 10;
        }
    }
}
