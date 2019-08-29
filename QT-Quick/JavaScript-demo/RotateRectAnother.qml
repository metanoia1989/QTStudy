import QtQuick 2.0
import "js/main.js" as Logic	// 导入JS文件

Rectangle {
    id: rect2
    width: 60
    height: 60
    gradient: Gradient { // 以黄蓝青渐变色填充，增强旋转视觉效果
        GradientStop { position: 0.0; color: "yellow" }
        GradientStop { position: 0.33; color: "blue" }
        GradientStop { position: 1.0; color: "aqua" }
    }
    Behavior on rotation { // 行为动画
        RotationAnimation {
            direction: RotationAnimation.Clockwise
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: rect2.rotation = Logic.getRandomNumber();
    }

}
