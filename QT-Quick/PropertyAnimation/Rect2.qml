import QtQuick 2.0


/* 信号处理 矩形 */
Rectangle {
    id: rect2
    width: 80
    height: 80
    color: "lightgreen"
    radius: 10
    Text {
        anchors.centerIn: parent
        font.pointSize: 12
        text: "信号处理"
    }
    MouseArea {
        anchors.fill: parent
        onClicked: PropertyAnimation {
            target: rect2	// 动画应用于标识rect2的矩形
            property: "y"	// Y轴方向的动画
            from: 30
            to: 300
            duration: 300
            loops: 3	// 运动3个周期
            easing.type: Easing.Linear	// 匀速线性运动
        }
    }
}
