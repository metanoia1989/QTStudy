import QtQuick 2.2

Item {
    width: 300
    height: 100
    TextInput {
        id: textInput
        echoMode: TextInput.PasswordEchoOnEdit
        focus: true
        onAccepted: { textInput.focus = false }
    }
}