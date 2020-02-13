import QtQuick 2.9
import QtQuick.Window 2.2
import QtDataVisualization 1.2

Window {
    visible: true
    width: 640
    height: 480

    Bars3D {
        width: parent.width
        height: parent.height
        scene {
            activeCamera.cameraPreset: Camera3D.CameraPresetIsometricRightHigh
            activeCamera.zoomLevel: 120
//            activeCamera.xRotation: -30
//            activeCamera.yRotation: 45
        }
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
        ListElement { year: "2012"; city: "Qulu"; expenses: "4200" }
        ListElement { year: "2012"; city: "Rauma"; expenses: "2100" }
        ListElement { year: "2013"; city: "Qulu"; expenses: "3960" }
        ListElement { year: "2013"; city: "Rauma"; expenses: "1990" }
    }
}
