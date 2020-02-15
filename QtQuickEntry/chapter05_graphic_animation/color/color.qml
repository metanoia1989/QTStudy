import QtQuick 2.12

Column {
    Rectangle {
        color: "gold"
        width: 400; height: 40
    }
    Rectangle {
        color: "transparent"
        width: 400; height: 40
    }
    Rectangle {
        color: "#ffa500"
        width: 400; height: 40
    }
    Rectangle {
        color: "#800000ff"
        width: 400; height: 40
    }
    Rectangle {
        color: Qt.tint("blue", "#55ff0000")
        width: 400; height: 40
    }
}
