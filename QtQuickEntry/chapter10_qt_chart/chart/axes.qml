import QtQuick 2.12
import QtQuick.Window 2.12
import QtCharts 2.3

Window {
    visible: true
    width: 640
    height: 480

    ChartView {
        title: "Line"
        anchors.fill: parent
        antialiasing: true

        ValueAxis {
            id: xAxis
            min: 0; max: 1000
            labelFormat: "%.1f"
            minorTickCount: 1
            tickCount: 5

            tickInterval: 300
            tickAnchor: 100
            tickType: ValueAxis.TicksDynamic
        }
        CategoryAxis {
            id: yAxis
            min: 0; max: 700
            labelsPosition: CategoryAxis.AxisLabelsPositionOnValue

            CategoryRange {
                label: "critical"
                endValue: 200
            }
            CategoryRange {
                label: "low"
                endValue: 400
            }
            CategoryRange {
                label: "normal"
                endValue: 700
            }
        }
        LineSeries {
            name: "LineSeries"
            axisX: xAxis
            axisY: yAxis

            XYPoint { x: 0; y: 0 }
            XYPoint { x: 100; y: 200 }
            XYPoint { x: 300; y: 500 }
            XYPoint { x: 600; y: 400 }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                xAxis.applyNiceNumbers()
            }
        }
    }
}
