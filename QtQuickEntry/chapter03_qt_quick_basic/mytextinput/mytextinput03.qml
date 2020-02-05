import QtQuick 2.2

Rectangle {
    width: 200
    height: 500

    TextInput {
        focus: true
        onAccepted: {
            text += " Qt"
        }
        onEditingFinished: {
            text = "hello"
            focus: false
        } 
    }

}
