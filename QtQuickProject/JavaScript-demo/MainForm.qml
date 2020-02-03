import QtQuick 2.0

Rectangle {
    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }
    TextEdit {
        id: textEdit
        visible: false
    }
    RotateRect {
        x: 50; y: 50
    }
    RotateRectAnother {
        x: 50; y: 150
    }
}
