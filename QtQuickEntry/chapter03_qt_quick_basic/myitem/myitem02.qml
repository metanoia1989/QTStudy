import QtQuick 2.12

// 两个相互重叠的透明矩形

Item {
    Rectangle {
        opacity: 0.5
        color: "red"
        width: 100; height: 100
        Rectangle {
            color: "blue"
            x: 50; y: 50; width: 100; height: 100
        }
    }
}
