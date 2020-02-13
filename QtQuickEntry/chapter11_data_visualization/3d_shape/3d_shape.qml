import QtQuick 2.12
import QtQuick.Window 2.12
import QtDataVisualization 1.3

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("3D系列形状")

    Bars3D {
        width: parent.width
        height: parent.height

        Bar3DSeries {
            itemLabelFormat: "@colLabel, @rowLabel, @valueLabel"
            mesh: Abstract3DSeries.MeshPyramid
            baseColor: "gold"
            singleHighlightColor: "lightgreen"
            itemLabelVisible: false
            meshAngle: 30

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
        ListElement { year: "2012"; city: "Qulu"; expenses: "4200" }
        ListElement { year: "2012"; city: "Rauma"; expenses: "2100" }
        ListElement { year: "2013"; city: "Qulu"; expenses: "3960" }
        ListElement { year: "2013"; city: "Rauma"; expenses: "1990" }
    }
}
