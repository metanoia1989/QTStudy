import QtQuick 2.0

SquareButton02 {
    id: squareButton
    onButtonClicked: {
       console.log("Clicked", xPos, yPos)
        randomizeColor()
    }
    Text { text: squareButton.pressed ? "Down" : "Up" }
}
