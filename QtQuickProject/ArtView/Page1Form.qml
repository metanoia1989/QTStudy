import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    property alias topic: topic
    property alias author: author

    SwipeView {
        id: view
        currentIndex: pageIndicator.currentIndex
        anchors.fill: parent

        Page {
            title: qsTr("蒙娜丽莎")
            Image {
                source: "images/mnls.jpg"
            }
        }
        Page {
            title: qsTr("大卫")
            Image {
                source: "images/dw.jpg"
            }
        }
        Page {
            title: qsTr("西斯廷圣母")
            Image {
                source: "images/sm.jpg"
            }
        }
    }

    PageIndicator {
        id: pageIndicator
        interactive: true
        count: view.count
        currentIndex: view.currentIndex
        anchors.bottom: parent.bottom // 位于页面底部
        anchors.horizontalCenter: parent.horizontalCenter // 位于底部的中央
    }

    Label {
        id: topic
        text: view.currentItem.title // 作品名作为当前页的标题
        font.family: "微软雅黑"
        font.bold: true
        font.pixelSize: 25
        anchors.right: parent.right
        anchors.rightMargin: 250

        TextArea {
            id: author
            font.family: "微软雅黑"
            font.pixelSize: 18
            anchors.top: parent.bottom	// 位于标题下方
        }
    }
}
