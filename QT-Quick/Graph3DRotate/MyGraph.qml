import QtQuick 2.0

Rectangle {	// 矩形作为图像显示区
    /* 矩形宽度、高度皆与图像尺寸吻合 */
    width: animg.width
    height: animg.height
    transform: Rotation {
        /* 设置图像原点 */
        origin.x: animg.width / 2
        origin.y: animg.height / 2
        axis {
            x: 0
            y: 1	// 绕 y 轴转动
            z: 0
        }
        NumberAnimation on angle {	// 定义角度 angle 上的动画
            from: 0
            to: 360
            duration: 20000
            loops: Animation.Infinite
        }
    }
    AnimatedImage {
        id: animg
        source: "images/foods.jpg"
    }
}
