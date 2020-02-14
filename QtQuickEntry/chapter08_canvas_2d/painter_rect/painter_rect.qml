import QtQuick 2.12

Canvas {
    width: 200; height:200

    onPaint: {
        var ctx = getContext("2d");
        ctx.fillStyle = "lightgrey"; // 填充颜色
        ctx.strokeStyle = "blue"; // 边框颜色
        ctx.lineWidth = 4; 	// 线宽 4px
        ctx.lineJoin = "round"; // 连接线段样式

        ctx.fillRect(20, 20, 160, 160);
        ctx.clearRect(30, 30, 140, 140);
        ctx.strokeRect(20, 20, 80, 80);
    }
}
