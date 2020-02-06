import QtQuick 2.2

Rectangle {
    id: widnow
    color: "black"; width: 240; height: 150
    Column {
        anchors.centerIn: parent; spacing: 15
        MyWidget02 {
            color: "lightblue"
            Component.onCompleted: console.log("1")
        }
        MyWidget02 {
            focus: true
            color: "palegreen"
            Component.onCompleted: console.log("2")
        }
        MyWidget02 {
            color: "red"
            Component.onCompleted: console.log("3")
        }
    }
}
