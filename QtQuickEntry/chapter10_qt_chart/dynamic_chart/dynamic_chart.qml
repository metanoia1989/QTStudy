import QtQuick 2.12
import QtQuick.Window 2.12
import QtCharts 2.3
import QtQuick.XmlListModel 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("加载数据动态创建图表")
    property int currentIndex: -1

    ChartView {
        id: chartView
        anchors.fill: parent
        title: qsTr("我的网站访问量")
        theme: ChartView.ChartThemeBlueCerulean
        antialiasing: true
    }

    XmlListModel {
        id: myXml
        source: "myxml.xml"
        query: "/qter/row"

        XmlRole { name: "month"; query: "month/string()" }
        XmlRole { name: "pv"; query: "pv/string()" }

        onStatusChanged: {
            if (status === XmlListModel.Ready) {
                console.log(myXml.count)
                timer.start()
            }
        }
    }

    Timer {
        id: timer
        interval: 1500
        repeat: true
        triggeredOnStart: true
        running: false
        onTriggered: {
            currentIndex++;
            if (currentIndex < myXml.count) {
                var lineSeries = chartView.series("2018");
                // 第一次运行时创建曲线
                if (!lineSeries) {
                    lineSeries = chartView.createSeries(ChartView.SeriesTypeSpline, "2018")
                    chartView.axisY().min = 200000;
                    chartView.axisY().max = 320000;
                    chartView.axisY().tickCount = 6;
                    chartView.axisY().titleText = qsTr("PV");
                    chartView.axisX().visible = false
                    lineSeries.color = "#87cefa";
                    lineSeries.pointsVisible = true
                    lineSeries.pointLabelsVisible = true
                    lineSeries.pointLabelsFormat = qsTr("@xPoint月份PV：@yPoint")
                    chartView.animationOptions = ChartView.SeriesAnimations
                }
                let { month, pv } = myXml.get(currentIndex);
                lineSeries.append(month, pv);
                if (month > 3) {
                    chartView.axisX().max = Number(month) + 1;
                    chartView.axisX().min = chartView.axisX().max  - 5;
                } else {
                    chartView.axisX().max = 5;
                    chartView.axisX().min = 0;
                }
                chartView.axisX().tickCount = chartView.axisX().max
                    - chartView.axisX().min + 1;
            } else {
                timer.stop();
                chartView.axisX().min = 0;
            }
        }
    }
}
