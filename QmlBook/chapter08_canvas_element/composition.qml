import QtQuick 2.12

Canvas {
    id: root
    width: 400; height: 200

    onPaint: {
        var ctx = getContext("2d");
        ctx.globalCompositeOperation = "xor";
        ctx.fillStyle = "#33a9ff";

        for (let i=0; i<40; i++) {
            ctx.beginPath();
            ctx.arc(Math.random()*400, Math.random()*200, 20, 0, 2*Math.PI);
            ctx.closePath();
            ctx.fill();
        }
    }
}
