import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.0

ApplicationWindow {
    visible: true
    width: 320
    height: 480
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    
    Component.onCompleted: {
        // setX(Screen.width / 2 - width / 2);
        // setY(Screen.height / 2 - height / 2);
    }
    
}