import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Image {
        id: img
        source: "https://pic2.zhimg.com/80/v2-222fb2a3cbe6c0fde111c197a301ba69_hd.jpg"
    }
    Image {
        source: "images/girls.jpg"
    }
}
