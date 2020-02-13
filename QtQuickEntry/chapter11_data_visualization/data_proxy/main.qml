import QtQuick 2.12
import QtQuick.Window 2.12
import QtDataVisualization 1.3

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("数据代理")

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
                rowRole: "timestamp"
                columnRole: "timestamp"
                valueRole: "income"
                rowRolePattern: /^(\d\d\d\d).*$/
                columnRolePattern: /^.*-(\d\d)$/
                rowRoleReplace: "\\1"
                columnRoleReplace: "\\1"
                multiMatchBehavior: ItemModelBarDataProxy.MMBCumulative
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
        ListElement { timestamp: "2006-01"; expenses: "-4"; income: "5" }
        ListElement { timestamp: "2006-02"; expenses: "-5"; income: "6" }
        ListElement { timestamp: "2006-02"; expenses: "-5"; income: "4" }
    }
}
