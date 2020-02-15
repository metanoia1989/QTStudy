import QtQuick 2.12

Rectangle {
    width: 360; height: 360; color: "lightgrey"
    Flickable {
        width: 200; height: 200
        contentWidth: image.width;
        contentHeight: image.height
        clip: true
        Image { id: image; source: "bigImage.jpg" }
    }
}
