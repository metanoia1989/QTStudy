import QtQuick 2.12

Canvas {
    width: 150; height: 150

    onPaint: {
        var ctx = getContext("2d");
        ctx.fillRect(10, 10, 50, 50);
        ctx.strokeText("1", 30, 70);
        ctx.translate(100, 0);
        ctx.rotate(Math.PI/4);
        ctx.fillRect(10, 10, 50, 50);
        ctx.strokeText("2", 30, 70);
    }
}
