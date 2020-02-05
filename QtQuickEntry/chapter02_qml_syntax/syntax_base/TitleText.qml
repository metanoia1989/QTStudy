import QtQuick 2.0

Text {
    property int size
    text: "<b>" + title + "</b>"
    font.pixelSize: size
}
