import QtQuick 2.12
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 320
    height: 280
    title: qsTr("对话框示例")
    MainForm {
        id: main
        anchors.fill: parent
        btnSelect.onClicked: dateDialog.open()	// 打开选择日期对话框
        btnOpen.onClicked: fileDialog.open()	// 打开标准文件对话框
        btnFont.onClicked: fontDialog.open()	// 打开标准字体对话框
        btnColor.onClicked: colorDialog.open()	// 打开标准颜色对话框
    }
    Dialog {
        id: dateDialog
        title: "选择日期"
        width: 275
        height: 300
        standardButtons: StandardButton.Save | StandardButton.Cancel
        onAccepted: main.date.text = calendar.selectedDate.toLocaleDateString()
        Calendar {
            id: calendar
            onDoubleClicked: dateDialog.click(StandardButton.save)	// 双击日历等同于单击Save按钮
        }
    }
    FileDialog {	// 文件标准对话框
        id: fileDialog
        title: "打开"
        nameFilters: ["Text files (*.txt)", "Image files (*.jpg *.png)", "All files (*)"]
        onAccepted: main.file.text = fileDialog.fileUrl
    }
    FontDialog {	// 字体标准对话框
        id: fontDialog
        title: "字体"
        font: Qt.font({ family: "宋体", pointSize:12, weight: Font.Normal })	// 初始默认选中的字体
        modality: Qt.WindowModal	// 模式对话框
        onAccepted: main.content.font = fontDialog.font
    }
    ColorDialog {	// 颜色标准对话框
        id: colorDialog
        title: "颜色"
        modality: Qt.WindowModal
        onAccepted: main.content.textColor = colorDialog.color
    }

}
