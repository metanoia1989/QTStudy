import QtQuick 2.12

Rectangle {
    width: 300; height: 180

    Canvas {
        id: canvas
        anchors.fill: parent
        onImageLoaded: {
            if (canvas.isImageError("http://www.baidu.com/img/bdlogo.gif")) {
                console.log("Image failed to load!");
            }
            var ctx = getContext("2d");
            ctx.drawImage("http://www.baidu.com/img/bdlogo.gif", 0, 0, 270, 129);
            canvas.requestPaint();
        }
    }

    Component.onCompleted: {
        canvas.loadImage("http://www.baidu.com/img/bdlogo.gif");
    }
}
