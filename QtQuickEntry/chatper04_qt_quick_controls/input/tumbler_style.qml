import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 250; height: 200

    Row {
        spacing: 20

        Tumbler {
            model: 15
            delegate: Text {
                text: qsTr("Item %1").arg(modelData + 1)
            }
        }
        Tumbler {
            id: control; model: 15
            background: Item {
                Rectangle {
                    opacity: control.enabled ? 0.2 : 0.1
                    border.color: "#000000"
                    width: parent.width; height: 1
                    anchors.top: parent.top
                }
                Rectangle {
                    opacity: control.enabled ? 0.2 : 0.1
                    border.color: "#000000"
                    width: parent.width; height: 1
                    anchors.bottom: parent.bottom
                }
            }
            delegate: Text {
                text: qsTr("Item %1").arg(modelData + 1); font: control.font
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                opacity: 1.0 - Math.abs(Tumbler.displacement) / (control.visibleItemCount / 2)
            }

            Rectangle {
                anchors.horizontalCenter: control.horizontalCenter
                y: control.height * 0.4; width: 40; height: 1; color: "#21be2b"
            }
            Rectangle {
                anchors.horizontalCenter: control.horizontalCenter
                y: control.height * 0.6; width: 40; height: 1; color: "#21be2b"
            }
        }
    }
}
