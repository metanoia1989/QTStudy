import QtQuick 2.12
import QtQuick.Window 2.2
import QtDataVisualization 1.3

Window {
    visible: true
    width: 640
    height: 480

    Scatter3D {
        width: parent.width
        height: parent.height
        axisX: xAxis
        axisY: yAxis
        axisZ: zAxis

        scene {
            activeCamera.cameraPreset: Camera3D.CameraPresetIsometricRightHigh
            activeCamera.zoomLevel: 120
        }
        theme: Theme3D {
            type: Theme3D.ThemeStoneMoss
            font.pointSize: 35
        }
        Scatter3DSeries {
            ItemModelScatterDataProxy {
                itemModel: dataModel
                xPosRole: "xPos"
                yPosRole: "yPos"
                zPosRole: "zPos"
            }
        }
    }
    ValueAxis3D {
        id: xAxis
        title: "X-Axis"
        titleVisible: true
        min: 1; max: 5
        subSegmentCount: 2
        labelFormat: "%.2f"
        labelAutoRotation: 45
    }
    ValueAxis3D {
        id: yAxis
        title: "Y-Axis"
        titleVisible: true
        min: 1; max: 3
        subSegmentCount: 2
        labelFormat: "%.2f"
        labelAutoRotation: 45
    }
    ValueAxis3D {
        id: zAxis
        title: "Z-Axis"
        titleVisible: true
        min: 1; max: 5
        subSegmentCount: 2
        labelFormat: "%.2f"
        labelAutoRotation: 45
    }

    ListModel {
        id: dataModel
        ListElement { xPos: "2.754"; yPos: "1.455"; zPos: "3.362" }
        ListElement { xPos: "3.164"; yPos: "2.022"; zPos: "4.348" }
        ListElement { xPos: "4.564"; yPos: "1.865"; zPos: "1.346" }
        ListElement { xPos: "1.068"; yPos: "1.224"; zPos: "2.983" }
        ListElement { xPos: "2.323"; yPos: "2.502"; zPos: "3.133" }
    }
}
