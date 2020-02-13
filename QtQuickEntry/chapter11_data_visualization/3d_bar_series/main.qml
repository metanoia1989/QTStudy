import QtQuick 2.12
import QtQuick.Window 2.12
import QtDataVisualization 1.3

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("3D Bar")

    Bars3D {
        width: parent.width
        height: parent.height
        barThickness: 0.8
        barSpacing: Qt.size(1.0, 3.0)
        floorLevel: 2700

        Bar3DSeries {
            itemLabelFormat: "@colLabel, @rowLabel: @valueLabel"
            ItemModelBarDataProxy {
                itemModel: dataModel
                rowRole: "year"
                columnRole: "city"
                valueRole: "expenses"
            }
        }
    }

    ListModel {
        id: dataModel
        ListElement { year: "2012"; city: "Oulu"; expenses: "4200" }
        ListElement { year: "2012"; city: "Rauma"; expenses: "2100" }
        ListElement { year: "2013"; city: "Oulu"; expenses: "3960" }
        ListElement { year: "2013"; city: "Rauma"; expenses: "1990" }
    }
}
