import QtQuick 2.12

Canvas {
    width: 120; height: 120

    onPaint: {
        var ctx = getContext("2d");
        var radial = ctx.createConicalGradient(60, 60, Math.PI/4);
        radial.addColorStop(0, "white");
        radial.addColorStop(0.5, "yellow");
        radial.addColorStop(1, "#333333");
        ctx.fillStyle = radial;
        ctx.fillRect(10, 10, 100, 100);
        ctx.strokeRect(10, 10, 100, 100);
    }
}
