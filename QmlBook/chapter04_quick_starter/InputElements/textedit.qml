import QtQuick 2.12

Rectangle {
    width: 136
    height: 120
    color: "linen"

    CustomTextEdit {
        id: input
        x: 8; y: 8
        width: 120; height: 104
        focus: true
        text: "Text Edit"
    }
}
