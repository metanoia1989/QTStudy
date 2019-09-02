import QtQuick 2.0

Rectangle {
    property alias mouseArea: mouseArea
    width: 360
    height: 360
    color: "lightgrey"	// 背景设为灰亮色以突出文本框效果
    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }
    /* 以下直接使用定义好的复合组件，生成所需文本框控件 */
    TextBox {	// 学号文本框
        id: tBx1
        x: 25; y: 25
        focus: true
        label: "学号"
        text: focus ? "" : "请输入内容..." // 获取焦点则清空提示文字
        KeyNavigation.tab: tBx2	// 按Tab键，焦点转移至姓名文本框
    }
    TextBox {	// 学号文本框
        id: tBx2
        x: 25; y: 60
        label: "姓名"
        text: focus ? "" : "请输入内容..." // 获取焦点则清空提示文字
        KeyNavigation.tab: tBx1
    }
}
