import QtQuick 2.12
import QtQuick.Window 2.12
import QtCharts 2.3

Window {
    visible: true
    width: 640
    height: 480

    ChartView {
        id: chart
        title: "PieSeries"
        anchors.fill: parent
        legend { alignment: Qt.AlignBottom }
        antialiasing: true

        PieSeries {
            id: pieSeries
            PieSlice { label: "Volkswagen"; value: 13.5  }
            PieSlice { label: "Toyoto"; value: 10.9  }
            PieSlice { label: "Ford"; value: 8.6  }
            PieSlice { label: "Skoda"; value: 8.2  }
            PieSlice { label: "Volvo"; value: 6.8  }
        }
    }

    Component.onCompleted: {
        pieSeries.append("Others", 52.0);
        var pieSlice = pieSeries.find("Volkswagen");
        pieSlice.exploded = true;
        pieSlice.labelVisible = true;
    }
}
