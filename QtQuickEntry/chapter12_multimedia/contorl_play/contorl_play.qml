import QtQuick 2.12
import QtMultimedia 5.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ApplicationWindow {
    id: window; width: 300; height: 300

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton { text: qsTr("播放"); onClicked: audio.play() }
            ToolButton { text: qsTr("暂停"); onClicked: audio.pause() }
            ToolButton { text: qsTr("停止"); onClicked: audio.stop() }
        }
    }
    ColumnLayout {
        spacing: 10; anchors.fill: parent

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Text { text: qsTr("进度：") }
            Slider {
                to: audio.duration;
                value: audio.position
                onValueChanged: audio.seek(value)
            }
        }
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Text { text: qsTr("音量：") }
            Slider {
                to: 1.0;
                value: audio.volume
                onValueChanged: audio.volume = value
            }
        }
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Text { text: qsTr("循环次数：") }
            SpinBox {
                value: 1;
                onValueChanged: audio.loops = value;
            }
        }
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Text { text: qsTr("播放速度：") }
            SpinBox {
                value: 1;
                stepSize: 1
                onValueChanged: audio.playbackRate = value;
            }
        }
    }

    Audio { id: audio; source: "music.mp3" }
}
