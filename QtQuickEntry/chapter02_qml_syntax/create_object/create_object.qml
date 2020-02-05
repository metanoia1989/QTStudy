import QtQuick 2.0
import "componentCreation-local.js" as MyScript

Rectangle {
    id: appWindow
    width: 300; height: 300
    Component.onCompleted: MyScript.createSpriteOjbects();
}

