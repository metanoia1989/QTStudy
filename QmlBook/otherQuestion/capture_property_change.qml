import QtQuick 2.12

Item {
    id: item
    property int prev: 0
    property int temp: value
    property int value: 0
    onValueChanged: {
        prev = temp;
        console.log("prev=" + prev);
        console.log("value=" + value)
        console.log("---------------");
    }

    Timer {
        interval: 1000
        repeat: true
        running: true
        onTriggered: {
            item.value = Math.round(Math.random() * 1000);
        }
    }
}
