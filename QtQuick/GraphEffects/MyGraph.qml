import QtQuick 2.0
import QtGraphicalEffects 1.0 	// QML 的图像特效元素类型库

Rectangle {	// 矩形作为图像显示区
    width: animg.width
    height: animg.height
    AnimatedImage {
        id: animg
        source: "images/foods.jpg"
    }
    BrightnessContrast {	// 特效元素 设置源元素的亮度和对比度
        id: bright
        anchors.fill: animg
        source: animg
    }
    SequentialAnimation {	// 定义串行组合动画
        id: imgAnim

        NumberAnimation {
            target: bright
            property: "brightness"		// BrightnessContrast 的属性 亮度 -1.0~1.0
            to: -0.5	// 变暗
            duration: 3000
        }

        NumberAnimation {
            target: bright
            property: "contrast"		// BrightnessContrast 的属性 对比度-1.0~1.0
            to: 0.25	// 对比度增强
            duration: 2000
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked:  {
            imgAnim.running = true	// 单击图像开启动画
        }
    }
}
