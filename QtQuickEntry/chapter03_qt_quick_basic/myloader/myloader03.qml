import QtQuick 2.2

// Loader 设置了锚或高宽，组件将会自适应为Loader的大小

Item {
    width: 200; height: 200
    Loader {
        anchors.centerIn: parent
        sourceComponent: rect
    }
    Component {
        id: rect
        Rectangle {
            width: 50
            height: 50
            color: "red"
        }
    }
}