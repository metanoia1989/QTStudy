import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2
import QtQuick.Extras 1.4

ApplicationWindow {
    visible: true
    width: 330
    height: 200
    title: qsTr("部分控件的外观")

    ColumnLayout {
        anchors.centerIn: parent

        RowLayout {
            Label {
                text: "忙指示器："
            }
            BusyIndicator {
                running: image.status === Image.Loading
            }
        }
        RowLayout {
            Label {
                text: "进度条："
            }
            ProgressBar {
                indeterminate: true
            }
        }
        RowLayout {
            Label {
                text: "滑动条："
            }
            Slider {
                from: 1
                to: 100
                value: 25
                stepSize: 5
                snapMode: Slider.SnapOnRelease // 滑动条的间断模式
            }
        }
        RowLayout {
            Label {
                text: "数值旋转框："
            }
            SpinBox {
                value: 50
            }
        }
    }
}
