import QtQuick 2.12
import QtQuick.Window 2.12
import QtCharts 2.3

Window {
    visible: true
    width: 400
    height: 320

    ChartView {
        title: "Percent Bar series"
        anchors.fill: parent
        legend { alignment: Qt.AlignBottom }
        antialiasing: true

        PercentBarSeries {
            axisX: BarCategoryAxis { categories: ["2007", "2008", "2009"] }
            BarSet { label: "Bob"; values: [2, 2, 3] }
            BarSet { label: "Susan"; values: [5, 1, 2] }
            BarSet { label: "James"; values: [3, 5, 8] }
        }
    }
}
