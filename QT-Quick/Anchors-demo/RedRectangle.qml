import QtQuick 2.0

/* 红色矩形 */
Rectangle {
    width: 64
    height: 32
    color: "red"
    border.color: Qt.lighter(color) // 填充色 50%
}
