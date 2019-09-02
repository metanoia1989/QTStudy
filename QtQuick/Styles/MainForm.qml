import QtQuick 2.12
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4	// Qt Quick 控件样式库

Item {
    id: window
    width: 600
    height: 240
    property int columnWidth: window.width/5	// 公共属性 用于设置空间列宽


    GridLayout {
        rowSpacing: 12
        columnSpacing: 30
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter // 主体窗口居中
        anchors.margins: 30	// 锚距为30
        /* 标准 Button 控件 */
        Button {
            text: "标准按钮"
            implicitWidth: columnWidth
        }
        /* 设置样式属性的 Button 控件 */
        Button {
            text: "样式属性"
            style: ButtonStyle {
                background: BorderImage {
                    source: control.pressed ? "images/button-pressed.png" : "images/button.png"
                    border { left: 4; right: 4; top: 4; bottom: 4}
                }
            }
            implicitWidth: columnWidth
        }
        /* 应用样式代理的 Button 控件 */
        Button {
            text: "样式代理"
            style: buttonStyle
            implicitWidth: columnWidth
        }
        /* 标准 TextField 控件 */
        TextField {
            Layout.row: 1
            implicitWidth: columnWidth
        }
        /* 设置样式属性的 TextField 控件 */
        TextField {
            style: TextFieldStyle {
                background: BorderImage {
                    source: "images/textfield.png"
                    border { left: 4; right: 4; top: 4; bottom: 4}
                }
            }
            implicitWidth: columnWidth
        }
        /* 应用样式代理的 TextField 控件 */
        TextField {
            style: textFieldStyle
            implicitWidth: columnWidth
        }
        /* 标准 Slider 控件 */
        Slider {
            id: slider1
            Layout.row: 2
            value: 0.5
            implicitWidth: columnWidth
        }
        /* 设置样式属性的 Slider 控件 */
        Slider {
            id: slider2
            value: 0.5
            implicitWidth: columnWidth
            style: SliderStyle {
                groove: BorderImage {
                    height: 6
                    source: "images/progress-background.png"
                    border { left: 6; right: 6; top: 1; bottom: 1}
                    BorderImage {
                        anchors.verticalCenter: parent.verticalCenter
                        source: "images/progress-fill.png"
                        border { left: 5; right: 5; top: 1; bottom: 1}
                        width: styleData.handlePosition	// 宽度至手柄（滑块）的位置
                        height: parent.height
                    }
                }
                handle: Item {
                    width: 13
                    height: 13
                    Image {
                        anchors.centerIn: parent
                        source: "images/slider-handle.png"
                    }
                }
            }
        }
        /* 应用样式代理的 Slider 控件 */
        Slider {
            id: slider3
            value: 0.5
            implicitWidth: columnWidth
            style: sliderStyle
        }
        /* 标准 ProgressBar 控件 */
        ProgressBar {
            Layout.row: 3	// 指定在GridLayou中的行号为3
            value: slider1.value	// 进度值与滑动条同步
            implicitWidth: columnWidth
        }

        /* 应用样式代理 ProgressBar 控件 */
        ProgressBar {
            value: slider2.value
            implicitWidth: columnWidth
            style: progressBarStyle
        }
        ProgressBar {
            value: slider3.value
            implicitWidth: columnWidth
            style: progressBarStyle2
        }

    }

    /* 定义各种样式代理*/
    property Component buttonStyle: ButtonStyle {
        // Button 控件所使用的样式代理
        background: Rectangle {	// 按钮背景为矩形
        implicitHeight: 22
        implicitWidth: columnWidth
        // 按钮被按下或获得焦点时变色
        color: control.pressed ? "darkGray" : control.activeFocus ? "#cdd" : "#ccc"
        antialiasing: true	// 平滑边缘反锯齿
        border.color: "gray"	// 灰色边框
        radius: height / 2	// 圆角形
        Rectangle {	// 该矩形为按钮自然状态 （未曾按下）的背景
            anchors.fill: parent
            anchors.margins: 1
            color: "transparent"	// 透明色
            antialiasing: true
            visible: !control.pressed	// 按钮未按下时可见
            border.color: "#aaffffff"
            radius: height/2
        }
        }
    }
    property Component textFieldStyle: TextFieldStyle {
        // TextField 控件所使用的样式代理
        background: Rectangle {	// 文本框背景为矩形
        implicitWidth: columnWidth
        color: "#f0f0f0"
        antialiasing: true
        border.color: "gray"
        radius: height/2
        Rectangle {
            anchors.fill: parent
            anchors.margins: 1
            color: "transparent"
            antialiasing: true
            border.color: "#aaffffff"
            radius: height/2
        }
        }
    }
    property Component sliderStyle: SliderStyle {
        // Slider 控件所使用的样式代理
        handle: Rectangle {	// 定义矩形作为滑块
        width: 18
        height: 18
        color: control.pressed ? "darkGray" : "lightGray"
        border.color: "gray"
        antialiasing: true
        radius: height/2
        Rectangle {	// 滑块呈圆形
            anchors.fill: parent
            anchors.margins: 1
            color: "transparent"
            antialiasing: true
            border.color: "#eee"
            radius: height/2
        }
        }
        groove: Rectangle {	// 定义滑动条的横槽
        height: 8
        implicitWidth: columnWidth
        implicitHeight: 22
        antialiasing: true
        color: "#ccc"
        border.color: "#777"
        radius: height/2
        Rectangle {	// 使得滑动条横槽两端有弧度 外观显得平滑
            anchors.fill: parent
            anchors.margins: 1
            color: "transparent"
            antialiasing: true
            border.color: "#66ffffff"
            radius: height/2
        }
        }
    }
    property Component progressBarStyle: ProgressBarStyle {
        // ProgressBarStyle 控件所使用的样式代理1
        background: BorderImage {
        source: "images/progress-background.png"
        border { left: 2; right: 2; top: 2; bottom: 2}
        }
        progress: Item {
        clip: true
        BorderImage {
            anchors.fill: parent
            anchors.rightMargin: (control.value < control.maximumValue) ? -4 : 0
            source: "images/progress-fill.png"
            border.left: 10; border.right: 10
            Rectangle {
            width: 1
            color: "#a70"
            opacity: 0.8
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 1
            anchors.right: parent.right
            visible: control.value < control.maximumValue	// 进度值未到头时始终课件
            anchors.rightMargin: -parent.anchors.rightMargin	// 两者锚定互补达到进度效果
            }
        }
        }

    }
    property Component progressBarStyle2: ProgressBarStyle {
        // ProgressBarStyle 控件所使用的样式代理1
        background: Rectangle {
        implicitWidth: columnWidth
        implicitHeight: 24
        color: "#f0f0f0"
        border.color: "gray"
        }
        progress: Rectangle {
        color: "#ccc"
        border.color: "gray"
        Rectangle {
            color: "transparent"
            border.color: "#44ffffff"
            anchors.fill: parent
            anchors.margins: 1
        }
        }
    }
}
