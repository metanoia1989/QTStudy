import QtQuick 2.12

Canvas {
    id: root
    width: 200; height: 300

    onPaint: {
        var ctx = getContext("2d");
        ctx.lineWidth = 4;
        ctx.strokeStyle = "blue";
        ctx.fillStyle = "steelblue";
        ctx.beginPath();
        ctx.moveTo(50, 50);
        ctx.lineTo(150, 50);
        ctx.lineTo(150, 150);
        ctx.lineTo(50, 150);
        ctx.closePath();
        ctx.fill();
        ctx.stroke();
    }
}
