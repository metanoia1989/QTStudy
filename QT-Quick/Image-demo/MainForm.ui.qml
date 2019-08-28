import QtQuick 2.4


Rectangle {
    width: 360
    height: 360

    Image {
        // 图片在窗口中的位置坐标
        x: 55
        y: 62
        // 宽和高均为原图的1/2
        width: 500/2; height: 426/2;
        source: "images/milk.jpg"
        fillMode: Image.PreserveAspectCrop // 等比缩放
        clip: true // 图片溢出时进行裁剪
    }

}
