import QtQuick 2.12
import QtQuick.Window 2.12
import QtCharts 2.3

Window {
    visible: true
    width: 740
    height: 480

    PolarChartView {
        title: "PolarChart"
        anchors.fill: parent
        legend { visible: false }
        antialiasing: true

        ValueAxis {
            id: axisAngular
            min: 0; max: 20
            tickCount: 9
        }
        ValueAxis {
            id: axisRadial
            min: -0.5; max: 1.5
        }
        SplineSeries {
            id: series1
            axisAngular: axisAngular
            axisRadial: axisRadial
            pointsVisible: true
        }
        ScatterSeries {
            id: series2
            axisAngular: axisAngular
            axisRadial: axisRadial
            markerSize: 10
        }
    }

    Component.onCompleted: {
        for (let i=0; i<=20; i++) {
            series1.append(i, Math.random());
            series2.append(i, Math.random());
        }
    }
}
