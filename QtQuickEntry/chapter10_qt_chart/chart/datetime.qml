import QtQuick 2.9
import QtQuick.Window 2.2
import QtCharts 2.3

Window {
    visible: true
    width: 640
    height: 480

    ChartView {
        title: "LineSeries"
        anchors.fill: parent
        antialiasing: true

        DateTimeAxis {
            id: xAxis
            format: "MM-dd"
            tickCount: 5
            min: new Date(2019, 0, 15)
            max: new Date(2019, 2, 1)

            color: "blue"
            gridLineColor: "lightgreen"
            labelsAngle: 90
            labelsColor: "red"
            labelsFont: { bold: true; pixelSize: 15 }
            shadesVisible: true
            shadesColor: "lightgrey"
            titleText: "date"
            titleFont: { bold: true; pixelSize: 30 }
        }

        LineSeries {
            name: "LineSeries"
            axisX: xAxis
            XYPoint { x: toMsecsSinceEpoch(new Date(2019, 0, 20)); y: 12 }
            XYPoint { x: toMsecsSinceEpoch(new Date(2019, 1, 13)); y: 18 }
            XYPoint { x: toMsecsSinceEpoch(new Date(2019, 1, 20)); y: 30 }
        }
    }

    function toMsecsSinceEpoch(date) {
        var msecs = date.getTime();
        return msecs;
    }
}
