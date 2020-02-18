import QtQuick 2.12

DarkSquare {
    id: root
    width: 400
    height: 120

    Row {
        id: row
        anchors.centerIn: parent
        spacing: 20
        RedSquare { }
        GreenSquare { }
        BlueSquare { }
    }
}
