import QtQuick 2.12

Canvas {
    id: root
    width: 400; height: 120

    onPaint: {
        var ctx = getContext("2d");
        ctx.drawImage("assets/ball.png", 10, 10);

        ctx.save();
        ctx.strokeStyle = "#ff2a68";

        ctx.beginPath();
        ctx.moveTo(110, 10);
        ctx.lineTo(155, 10);
        ctx.lineTo(135, 55);
        ctx.closePath();
        ctx.clip();
        ctx.drawImage("assets/ball.png", 100, 10);
        ctx.stroke();
        ctx.restore();
    }

    Component.onCompleted: {
        loadImage("assets/ball.png");
    }
}
