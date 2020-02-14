import QtQuick 2.12

Rectangle {
    width: 300; height: 100

    Canvas {
        id: canvas
        anchors.fill: parent
        onImageLoaded: {
            if (canvas.isImageError("http://www.baidu.com/img/bdlogo.gif")) {
                console.log("Image failed to load!");
            }
            var ctx = getContext("2d");
            ctx.drawImage("http://www.baidu.com/img/bdlogo.gif", 0, 0, 270, 129);
            var img = ctx.getImageData(60, 50, 120, 40);
            ctx.strokeRect(60, 50, 120, 40);
            ctx.drawImage(img, 10, 100)
            canvas.requestPaint();

        }
    }

    Component.onCompleted: {
        canvas.loadImage("http://www.baidu.com/img/bdlogo.gif");
    }
}
