import QtQuick 2.0

Rectangle {
    id: rect
    width: 60
    height: 60
    gradient: Gradient { // 以黄蓝青渐变色填充，增强旋转视觉效果
        GradientStop { position: 0.0; color: "yellow" }
        GradientStop { position: 0.33; color: "blue" }
        GradientStop { position: 1.0; color: "aqua" }
    }
    function getRandomNumber() { // 定义JavaScript 函数
        return Math.random() * 360; // 随机旋转的角度值
    }
    Behavior on rotation { // 行为动画
        RotationAnimation {
            direction: RotationAnimation.Clockwise
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: rect.rotation = getRandomNumber();
    }
}
