import QtQuick 2.12
import QtGraphicalEffects 1.0

Item {
    width: 300; height: 300

    Image {
        id: bug; source: "images/bug.png"
        sourceSize: Qt.size(parent.width, parent.height)
        smooth: true; visible: false
    }

    GammaAdjust {
        anchors.fill: bug; source: bug;
        gamma: 0.45
    }
}
