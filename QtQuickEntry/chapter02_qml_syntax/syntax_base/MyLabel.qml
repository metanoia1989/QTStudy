import QtQuick 2.0

Text {
    default property var someText
    text: "Hello, " + someText.text
}
