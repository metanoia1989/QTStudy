import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Item {
    width: 890
    height: 640
    /* 定义属性别名，在main.qml中引用各个控件 */
    property alias img: img	// 图像元素
    property alias desat: desat // 特效元素 控制色彩饱和度
    property alias size: size  // 尺寸 滑动条
    property alias colorful: colorful // 彩色 开关
    property alias btn: btn	// 灰度值 按钮
    property alias progressbar: progressbar // 图像元素 显示图片用

    Image {
        id: img
        x: 10; y:10
        width: 614.4
        height: 384
        source: "images/foods.jpg"
        fillMode: Image.Stretch // 拉伸模式才能调整尺寸
        clip: true
    }

    BusyIndicator {
        x: 317.2; y: 202
        running: img.width < 614.4 * 0.4 // 当前画面宽度缩小为原来的0.4时运行
    }

    Desaturate {	// 饱和度特效元素
        id: desat
        anchors.fill: img
        source: img
    }

    RowLayout {
        anchors.left: img.left	// 与画面左锚定
        y: 399
        spacing: 5
        Label {
            text: "尺寸"
        }
        Slider {	// 滑动条
            id: size
            maximumValue: 1.0	// 最大值
            minimumValue: 0.1 	// 最小值
            stepSize: 0.1	// 步进值
            value: 1.0	// 初始值
        }
        Label {
            text: "彩色"
        }
        Switch {	// 开关
            id: colorful
            checked: true
        }
        Button {
            id: btn
            text: "灰度值"
        }
        ProgressBar {
            id: progressbar
        }
    }
    ColumnLayout {	// 列布局
        anchors.top: img.top	// 与画面顶部锚定
        x: 629.4
        spacing: 10
        RowLayout {
            spacing: 5
            Label {
                text: "食物"
                font.pixelSize: 14
                font.bold: true
            }
            SpinBox {
                id: age
                decimals: 0	// 精度 小数位
                value: 16
                minimumValue: 4
                maximumValue: 24
                suffix: "岁"		// 数值单位
                font.pixelSize: 14
            }
        }
        Label {
            anchors.horizontalCenter: birthday.horizontalCenter	// 与日历居中对齐
            text: "生日"
            font.pixelSize: 14
            font.bold: true
            color: "magenta"	// 品红色
        }
        Calendar {
            id: birthday
            minimumDate: "1991-09-01"
            visibleYear: 2017 - age.value // 同步计算出生年月
            visibleMonth: 8	// 9月
        }
    }
}
