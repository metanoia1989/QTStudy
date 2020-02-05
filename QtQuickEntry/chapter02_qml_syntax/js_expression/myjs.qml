import QtQuick 2.0

Item {
    width: 500
    height: 500
    Rectangle {
        id: rect
        width: 100
        color: "yellow"
    }
    Component.onCompleted: {
        rect.height = Qt.binding(() => {
            console.log("what is this: ", this)
            return this.width * 2;
        })
        console.log("rect.height = " + rect.height)
    }
}
