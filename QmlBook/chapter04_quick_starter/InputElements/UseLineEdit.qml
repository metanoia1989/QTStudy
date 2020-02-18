import QtQuick 2.12

Rectangle {
    width: 200
    height: 80
    color: "linen"

    LineEdit {
        id: input1
        x: 8; y: 8
        focus: true
        text: "Text Input 1"
        KeyNavigation.tab: input2
        Component.onCompleted: {
            console.log(input1.height);
        }
    }
    LineEdit {
        id: input2
        x: 8; y: 36
        text: "Text Input 2"
        KeyNavigation.tab: input1
        onFocusChanged: print('focus')
    }
}
