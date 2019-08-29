import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Item {	// QML 通用的根元素
    width: 640
    height: 480
    /* 定义属性别名，在 main.qml 中引用这两个按钮控件 */
    property alias button1: button1
    property alias button2: button2

    RowLayout {	//行布局
        anchors.centerIn: parent // 在窗口中居中

        Button {	// 按钮控件： Press Me 1
            id: button1
            text: qsTr("Press Me 1")
        }
        Button {	// 按钮控件： Press Me 2
            id: button2
            text: qsTr("Press Me 2")
        }

    }
}
