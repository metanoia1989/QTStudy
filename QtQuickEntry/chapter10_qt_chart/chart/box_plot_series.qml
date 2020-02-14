import QtQuick 2.12
import QtQuick.Window 2.12
import QtCharts 2.3

Window {
    visible: true
    width: 640
    height: 480

    ChartView {
        id: chart
        title: "Box Plot series"
        anchors.fill: parent
        legend { alignment: Qt.AlignBottom }
        antialiasing: true

        BoxPlotSeries {
            id: plotSeries
            name: "Income"
            BoxSet { label: "Jan"; values: [3, 4, 5.1, 6.2, 8.5 ] }
            BoxSet { label: "Feb"; values: [5, 6, 7.5, 8.6, 11.8 ] }
            BoxSet { label: "Mar"; values: [3.2, 5, 5.7, 8, 9.2 ] }
            BoxSet { label: "Apr"; values: [3.8, 5, 6.4, 7, 8 ] }
            BoxSet { label: "May"; values: [4, 5, 5.2, 6, 7 ] }
        }
    }
}
