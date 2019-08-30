import QtQuick 2.12
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3

Item {
    width: 320
    height: 280
    /* 定义属性别名 在 main.qml 中引用各个组件 */
    property alias date: date	// 日期文本框
    property alias btnSelect: btnSelect // 选择...按钮
    property alias file: file 	// 文件文本框
    property alias btnOpen: btnOpen // 打开按钮
    property alias content: content // 文本区
    property alias btnFont: btnFont // 字体...按钮
    property alias btnColor: btnColor // 颜色...按钮

    ColumnLayout {
        anchors.centerIn: parent
        RowLayout {	// 提供日期选择功能
            Label {
                text: "日期："
            }
            TextField {
                id: date
            }
            Button {
                id: btnSelect
                text: qsTr("选择...")
            }
        }
        RowLayout {	// 提供文件选择功能
            Label {
                text: "文件："
            }
            TextField {
                id: file
            }
            Button {
                id: btnOpen
                text: qsTr("打开...")
            }
        }
        TextArea {	// 文本区
            id: content
            Layout.fillWidth: true
            text: "我喜欢 Qt Quick"
            font.pixelSize: 14
        }
        RowLayout { // 提供字体、颜色选择功能
            Layout.alignment: Qt.AlignRight
            Button {
                id: btnFont
                text: qsTr("字体...")
            }
            Button {
                id: btnColor
                text: qsTr("颜色...")
            }
        }

    }
}
