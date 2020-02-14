import QtQuick 2.12
import QtQuick.Window 2.12
import QtCharts 2.3
import QtGraphicalEffects 1.0

Window {
    visible: true
    width: 640
    height: 480
    color: "black"

    ChartView {
        id: chartView
        title: qsTr("我的图表")
        titleColor: Qt.lighter("blue")
        titleFont: { bold: true; pointSize: 20 }
        plotAreaColor: "lightgrey"
        backgroundColor: Qt.lighter("yellow")
//        backgroundColor: "transparent"
        backgroundRoundness: 25
        dropShadowEnabled: true

        anchors.fill: parent
        anchors.margins: 20

        antialiasing: true
        animationOptions: ChartView.AllAnimations
        animationDuration: 5000

        LineSeries {
            name: "LineSeries"
            XYPoint { x: 0; y: 0 }
            XYPoint { x: 1.1; y: 2.1 }
            XYPoint { x: 1.9; y: 3.3 }
        }
    }

    Glow {
        id: glow
        anchors.fill: chartView
        radius: 13
        samples: 37
        color: "white"
        source: chartView
    }
}
