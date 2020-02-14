import QtQuick 2.12
import QtQuick.Window 2.12
import QtCharts 2.3

Window {
    visible: true
    width: 740
    height: 480

    ChartView {
        id: chart
        title: "Box Plot series"
        anchors.fill: parent
        legend { alignment: Qt.AlignBottom }
        antialiasing: true

        CandlestickSeries{
            name: "Acme Ltd."
            CandlestickSet { timestamp: 1435708800000; open: 690;
                high: 694; low: 599; close: 660 }
            CandlestickSet { timestamp: 1435795200000; open: 669;
                high: 669; low: 669; close: 669 }
            CandlestickSet { timestamp: 1436140800000; open: 485;
                high: 623; low: 485; close: 600 }
            CandlestickSet { timestamp: 1436227200000; open: 589;
                high: 615; low: 377; close: 569 }
            CandlestickSet { timestamp: 1436313600000; open: 464;
                high: 464; low: 254; close: 254 }
        }
    }
}
