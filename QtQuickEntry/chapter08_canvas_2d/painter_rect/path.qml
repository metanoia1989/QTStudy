import QtQuick 2.12

Canvas {
    width: 470; height: 230

    onPaint: {
        var ctx = getContext("2d");
        ctx.strokeStyle = Qt.rgba(0.1, 0.1, 0.1, 0.2);
        ctx.lineWidth = 4;

        // 循环体外，每次 stroke，新的路径会被添加到已有路径中，外侧会绘制多次
        ctx.beginPath();
        for (let i=0; i<5; ++i) {
            ctx.rect(10+i*20, 10+i*20, 210-i*40, 210-i*40);
            ctx.stroke();
        }
        for (let j=0; j<5; ++j) {
            ctx.beginPath();
            ctx.rect(240+j*20, 10+j*20, 210-j*40, 210-j*40);
            ctx.stroke();
        }
    }
}
