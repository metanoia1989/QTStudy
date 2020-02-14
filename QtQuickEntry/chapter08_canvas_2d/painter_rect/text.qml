import QtQuick 2.12

Canvas {
    width: 210; height: 200

    onPaint: {

        var ctx = getContext("2d");
        ctx.fillStyle = "green";
        ctx.strokeStyle = "blue";
        ctx.lineWidth = 2;
        ctx.font = "bold 50px Arial";

        var text = "QML Canvas";
        context.fillText(text, 10, 80);
        context.strokeText(text, 10, 150);
//        ctx.fillText(text, 10, 80);
//        ctx.strokeText(text, 10, 150);
        var s = JSON.stringify(context);
        console.log("what is context: ", s);
    }
}
