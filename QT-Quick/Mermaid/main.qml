import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 890
    height: 460
    title: qsTr("Mermaid")
    MainForm {
        anchors.fill: parent
        size.onValueChanged: {	// 拖动滑块所要执行的代码
            var scale = size.value; // 缩放比率
            img.width = 500 * scale; // 宽度缩放
            img.height = 397 * scale; // 高度缩放
        }
        colorful.onCheckedChanged: { // 开关切换彩色/白色
            desat.desaturation = colorful.checked ? 0.0 : 1.0;
        }
        btn.onClicked: { // 单击灰度值>>按钮
            if (desat.desaturation < 0.9) {
                desat.desaturation += 0.1;	// 增加灰度
            } else {
                desat.desaturation -= 0.1; // 变回彩色
            }
            progressbar.value = desat.desaturation; // 进度条的进度与灰度同步改变
        }
    }
}
