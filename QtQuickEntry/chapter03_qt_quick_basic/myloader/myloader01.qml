import QtQuick 2.2

Item {
    width: 200; height: 200
    Loader { id: pageLoader }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            pageLoader.source = "Page1.qml"
            console.log(pageLoader.item)
        } 
    }
}