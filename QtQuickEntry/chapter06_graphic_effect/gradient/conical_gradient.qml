import QtQuick 2.12
import QtGraphicalEffects 1.0

Item {
    width: 300; height: 300

    Image {
        id: butterfly
        source: "images/butterfly.png"
        sourceSize: Qt.size(parent.width, parent.height)
        smooth: true; visible: false
    }

    ConicalGradient {
        anchors.fill: parent
        source: butterfly
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#f0f0f0" }
            GradientStop { position: 0.5; color: "#000000" }
            GradientStop { position: 1.0; color: "#f0f0f0" }
        }
    }
}
