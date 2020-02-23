import QtQuick 2.0

Item {
    property string text: time.text
    width: 100
    height: 100
    Text {
        id: time
        text: qsTr("text")
    }
}
