import QtQuick 2.12

Canvas {
    width: 500; height: 200

    onPaint: {
        var ctx = getContext("2d");
        ctx.fillStyle = "grey";
        ctx.save();
        ctx.shadowBlur = 20;
        ctx.shadowColor = "blue";
        ctx.fillRect(60, 30, 100, 100);
        ctx.restore();
        ctx.save();
        ctx.shadowBlur = 20;
        ctx.shadowColor = "green";
        ctx.shadowOffsetX = 15;
        ctx.shadowOffsetY = 15;
        ctx.fillRect(200, 30, 100, 100);
        ctx.restore();
        ctx.fillRect(350, 30, 100, 100);
    }
}
