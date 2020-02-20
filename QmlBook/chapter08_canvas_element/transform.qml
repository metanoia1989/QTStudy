import QtQuick 2.12

Canvas {
    id: root
    width: 240; height: 120

    onPaint: {
        var ctx = getContext("2d");
        ctx.lineWidth = 4;
        ctx.strokeStyle = "blue";

        ctx.translate(root.width/2, root.height/2);

        ctx.beginPath();
        ctx.rect(-20, -20, 40, 40);
        ctx.stroke();

        ctx.rotate(Math.PI/4);
        ctx.strokStyle = "green";

        ctx.beginPath();
        ctx.rect(-20, -20, 40, 40);
        ctx.stroke();
    }
}
