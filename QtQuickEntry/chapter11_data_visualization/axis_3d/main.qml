import QtQuick 2.12
import QtQuick.Window 2.12
import QtDataVisualization 1.3

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("3D坐标轴")

    Bars3D {
        width: parent.width
        height: parent.height

        rowAxis: rAxis
        columnAxis: cAxis
        valueAxis: vAxis

        Bar3DSeries {
            itemLabelFormat: "@colLabel, @rowLabel, @valueLabel"
            ItemModelBarDataProxy {
                itemModel: dataModel
                rowRole: "year"
                columnRole: "month"
                valueRole: "expenses"
                // 筛选过滤
//                rowCategories: ["2019"]
//                autoRowCategories: false
//                columnCategories: ["01"]
//                autoColumnCategories: false
            }
        }
    }

    ValueAxis3D {
        id: vAxis
        title: "Y-Axis"
        titleVisible: true
        min: 0; max: 30
        subSegmentCount: 2
        labelFormat: "%.2f"
    }
    CategoryAxis3D {
        id: rAxis
        title: "X-Axis"
        titleVisible: true
        labelAutoRotation: 30
    }
    CategoryAxis3D {
        id: cAxis
        title: "Z-Axis"
        titleVisible: true
        labels: ["January", "February"]
    }

    ListModel {
        id: dataModel
        ListElement { year: "2018"; month: "01"; income: "16" }
        ListElement { year: "2018"; month: "02"; income: "28" }
        ListElement { year: "2019"; month: "01"; income: "22" }
        ListElement { year: "2019"; month: "02"; income: "25" }
    }
}
