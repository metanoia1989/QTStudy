import QtQuick 2.12

// 层叠属性 z

Item {
    Rectangle {
        // z: 1
        color: "red"
        width: 100; height: 100
    }
    Rectangle {
        color: "blue"
        x: 50; y: 50; width: 100; height: 100
    }
}
