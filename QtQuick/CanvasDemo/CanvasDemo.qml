import QtQuick 2.0

Canvas {
    id: root
    width: 200; height: 200
    // 重写绘制函数
    onPaint: {
        // 获得2d上下文对象
        var ctx = getContext("2d");
        // 设置画笔
        ctx.lineWidth = 4;
        ctx.strokeStyle = "blue";
        // 设置填充
        ctx.fillStyle = "steelblue";
        // 开始绘制路径
        ctx.beginPath();
        // 移动到左上点作为起始点
        ctx.moveTo(50, 50);
        // 上边线
        ctx.lineTo(150, 50);
        // 右边线
        ctx.lineTo(150, 150);
        // 底边线
        ctx.lineTo(50, 150);
        // 左边线并结束路径
        ctx.closePath();
        // 使用填充填充路径
        ctx.fill();
        // 使用画笔绘制边线
        ctx.stroke();
    }
}
