import QtQuick 2.12
import QtQuick.Window 2.12
import "script.mjs" as MyScript

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    MouseArea {
        anchors.fill: parent
        onClicked: {
            MyScript.showCalculations(10);
            console.log("Call factorial() from QML: ",
                        MyScript.factorial(10))
        }
    }
}
