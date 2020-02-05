import QtQuick 2.2

Item {
    width: 200
    height: 150
    TextInput {
        validator: IntValidator { bottom: 11; top: 31 }
        focus: true
    }
}