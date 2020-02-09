import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 250; height:200

    Column {
        spacing: 20
        anchors.centerIn: parent

        DelayButton { text: qsTr("Default DelayButton") }

        DelayButton {
            id: control
            text: qsTr("Styled DelayButton")
            checked: true

            contentItem: Text {
                text: control.text; font: control.font
                opacity: enabled ? 1.0 : 0.3; color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
            background: Rectangle {
                implicitWidth: 120; implicitHeight: 120
                opacity: enabled ? 1 : 0.3
                color: control.down ? "#17a81a" : "#21be2b"

                readonly property real size: Math.min(control.width, control.height)
                radius: size / 2; width: size; height: size
                anchors.centerIn: parent

                Canvas {
                    id: canvas
                    anchors.fill: parent

                    Connections {
                        target: control;
                        onProgressChanged: canvas.requestPaint()
                    }

                    onPaint: {
                        var ctx = getContext("2d");
                        ctx.clearRect(0, 0, width, height);
                        ctx.strokeStyle = "white";
                        ctx.lineWidth = parent.size / 20;
                        ctx.beginPath();
                        var startAngle = Math.PI / 5 * 3
                        var endAngle = startAngle + control.progress * Math.PI / 5 * 9;
                        ctx.arc(width / 2, height / 2, width / 2 - ctx.lineWidth / 2 - 2, startAngle, endAngle);
                        ctx.stroke();
                    }
                }
            }
        }
    }
}
