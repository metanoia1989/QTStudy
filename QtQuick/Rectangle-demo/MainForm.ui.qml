import QtQuick 2.4


Rectangle {
    property alias mouseArea: mouseArea
    property alias topRect: topRect
    width: 360
    height: 360
    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }

    /* 添加定义两个Rectangle对象 */
    Rectangle {
        rotation: 45 // 旋转45
        x: 40
        y: 60
        width: 100
        height: 100
        color: 'red' // 以红色填充
    }

    Rectangle {
        id: topRect
        opacity: 0.6 // 设置透明度为60%
        scale: 0.8 // 缩小为原尺寸的80%
        x: 135
        y: 60
        width: 100
        height: 100
        radius: 8 // 绘制圆角矩形
        gradient: Gradient {
            GradientStop { position: 0.0; color: "aqua" }
            GradientStop { position: 1.0; color: "teal" }
        }
        border { width: 3; color: "blue" } // 3像素的蓝色边框
    }
}
