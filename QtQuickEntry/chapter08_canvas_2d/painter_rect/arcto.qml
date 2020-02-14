import QtQuick 2.12

Canvas {
    width: 160; height: 160

    onPaint: {
        var ctx = getContext("2d");
        ctx.lineWidth = 2;

        ctx.beginPath();
        ctx.moveTo(20, 20);
        ctx.lineTo(100, 20);
        ctx.arcTo(150, 20, 150, 70, 50);
        ctx.lineTo(150, 120);
        ctx.stroke();
    }
}
