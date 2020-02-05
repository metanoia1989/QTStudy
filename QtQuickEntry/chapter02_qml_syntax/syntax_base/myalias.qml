// Button.qml
import QtQuick 2.0

Rectangle {
    property alias buttonText: textItem.text
    width: 100; height: 30; color: "yellow"
    Text {
        id: textItem
        text: "Hello Qt Quick"
    }
}

// other.qml
Button { buttonText: "click Me" }
