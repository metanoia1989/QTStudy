import QtQuick 2.0

/* 蓝色矩形 */
Rectangle {
    width: 80
    height: 50
    color: "blue"
    border.color: Qt.lighter(color) // 填充色 50%
}
