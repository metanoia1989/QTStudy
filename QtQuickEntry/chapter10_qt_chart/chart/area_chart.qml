import QtQuick 2.12
import QtQuick.Window 2.12
import QtCharts 2.3

Window {
    visible: true
    width: 640
    height: 480

    ChartView {
        title: "AreaSeries"
        anchors.fill: parent
        antialiasing: true

        ValueAxis {
            id: valueAxis
            min: 2000
            max: 2011
            tickCount: 12
            labelFormat: "%.0f"
        }
        AreaSeries {
            name: "Area1"
            axisX: valueAxis
            upperSeries: LineSeries {
                XYPoint { x: 2000; y: 1 }
                XYPoint { x: 2001; y: 4 }
                XYPoint { x: 2002; y: 3 }
                XYPoint { x: 2003; y: 2 }
                XYPoint { x: 2004; y: 1 }
                XYPoint { x: 2005; y: 0 }
                XYPoint { x: 2006; y: 1 }
            }
            onClicked: console.log("onClicked: " + point.x + ", " + point.y)
        }
        AreaSeries {
            name: "Area2"
            axisX: valueAxis
            upperSeries: LineSeries {
                XYPoint { x: 2007; y: 1 }
                XYPoint { x: 2008; y: 4 }
                XYPoint { x: 2009; y: 3 }
                XYPoint { x: 2010; y: 2 }
                XYPoint { x: 2011; y: 1 }
            }
            lowerSeries: LineSeries {
                XYPoint { x: 2007; y: 0 }
                XYPoint { x: 2008; y: 2 }
                XYPoint { x: 2009; y: 1 }
                XYPoint { x: 2010; y: 1 }
                XYPoint { x: 2011; y: 0 }
            }
        }
    }
}
