import QtQuick 2.12


Rectangle {
    property alias mouseArea: mouseArea
    property alias chgRect1: changingRect1 // 矩形 changingRect1 属性别名
    property alias chgRect2: changingRect2 // 矩形 changingRect2 属性别名
    property alias rRect: redRect // 红矩形 redRect 属性别名

    width: 360
    height: 360

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }

    /* 使用 Anchor 对三个矩形元素进行横向布局 */
    BlueRectangle { // 蓝色矩形
       id: blueRect
       anchors.left: parent.left 	// 与窗口左锚线锚定
       anchors.top: parent.top	// 与窗口顶锚线锚定
       anchors.leftMargin: 25	// 左锚边距 与窗口的左边距
       anchors.topMargin: 25	// 顶锚边距 与窗口的顶边距
    }

    GreenRectangle { // 绿色矩形
       id: greenRect
       anchors.left: blueRect.right// 与蓝矩形右锚线锚定
       anchors.top: blueRect.top	// 与蓝矩形顶锚线锚定
       anchors.leftMargin: 40	// 左锚边距 与蓝矩形的间距
    }

    RedRectangle { // 红色矩形
       id: redRect
       anchors.left: greenRect.right// 与绿矩形右锚线锚定
       anchors.top: greenRect.top	// 与绿矩形顶锚线锚定
       anchors.leftMargin: 40	// 左锚边距 与绿矩形的间距
    }

}
