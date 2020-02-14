import QtQuick 2.12

Canvas {
    width: 120; height: 120

    onPaint: {
        var ctx = getContext("2d");
        ctx.lineWidth = 2;

        var radial = ctx.createRadialGradient(30, 70, 5, 60, 50, 80);
        radial.addColorStop(0, "white");
        radial.addColorStop(0.5, "yellow");
        radial.addColorStop(1, "#333333");
        ctx.fillStyle = radial;
        ctx.fillRect(10, 10, 100, 100);
        ctx.strokeRect(10, 10, 100, 100);
    }
}
