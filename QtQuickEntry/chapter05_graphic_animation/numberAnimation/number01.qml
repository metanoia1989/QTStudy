import QtQuick 2.0

Rectangle {
    width: 100; height: 100
    color: "red"

    property bool run: false

    NumberAnimation on x { 
        to: 50; 
        from: 30
        duration: 1000 
        running: run
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            run = !run;
        }
    }
    
}
