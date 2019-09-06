import QtQuick 2.0

Canvas {
    id: shadow
    width: 280; height:120
    onPaint: {
        var ctx = getContext("2d");
        // 背景矩形
        ctx.strokeStyle = "#fff";
        ctx.fillRect(0, 0, shadow.width, shadow.height);
        // 设置阴影属性
        ctx.shadowColor = "blue";
        ctx.shadowOffsetX = 2;
        ctx.shadowOffsetY = 2;
        ctx.shadowBlur = 10;
        // 设置字体并绘制
        ctx.font = 'bold 80px sans-serif';
        ctx.fillStyle = '#000';
        ctx.fillText("地球", 30, 80);
    }
}
