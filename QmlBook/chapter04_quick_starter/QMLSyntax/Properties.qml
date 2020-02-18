import QtQuick 2.0

Text {
    id: thisLabel
    x: 24; y: 16
    height: 2 * width
    property int times: 24
    property alias anotherTimes: thisLabel.times
    text: "Greetings" + times
    font.family: "Ubuntu"
    font.pixelSize: 24
//    KeyNavigation.tab: otherLabel
    onHeightChanged: console.log("height: ", height)
    focus: tab
    color: focus ? "red" : "black"
}
