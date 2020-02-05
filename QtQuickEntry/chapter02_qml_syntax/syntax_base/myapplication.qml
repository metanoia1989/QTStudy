import QtQuick 2.0

SquareButton {
    onActivated: console.log("Activated at"
                             + xPosition + "," + yPosition)
    onDeactivated: console.log("Deactivated!")
}
