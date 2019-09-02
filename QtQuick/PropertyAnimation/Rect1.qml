import QtQuick 2.0

/* 属性值源 矩形 */
Rectangle {
    width: 80
    height: 80
    color: "orange"
    radius: 10
    Text {
        anchors.centerIn: parent
        font.pointSize: 12
        text: "属性值源"
    }
    PropertyAnimation on x {
        from: 50	// 起点
        to: 500		// 终点
        duration: 3000		// 运动时间
        loops: Animation.Infinite	// 无限循环
        easing.type: Easing.OutBounce	// 达到目标值时的反弹效果
    }
}
