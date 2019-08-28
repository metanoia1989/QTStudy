import QtQuick 2.4

Rectangle {
    property alias mouseArea: mouseArea
    width: 200; height: 200

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }

    Flow {
        anchors.fill: parent
        anchors.margins: 15
        spacing: 5
        // 以下是 Flow 定位的元素成员
        RedRectangle {}
        GreenRectangle {}
        BlueRectangle {}
    }
    Row {
        x: 25
        y: 125
        spacing: 10
        layoutDirection: Qt.RightToLeft // 元素从右到左排列
        // 以下是 Row 定位的元素成员
        RedRectangle {}
        GreenRectangle {}
        BlueRectangle {}
    }
    Column {
        x: 25
        y: 220
        spacing: 2
        // 以下是 Column 定位的元素成员
        RedRectangle {}
        GreenRectangle {}
        BlueRectangle {}
    }
    Grid {
        x: 140
        y: 220
        columns: 3
        spacing: 5
        // 以下是 Grid 定位的元素成员
        BlueRectangle {}
        BlueRectangle {}
        BlueRectangle {}
        BlueRectangle {}
        BlueRectangle {}
    }

}
