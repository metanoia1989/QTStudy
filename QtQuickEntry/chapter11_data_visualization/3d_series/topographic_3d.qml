import QtQuick 2.12
import QtQuick.Window 2.12
import QtDataVisualization 1.3

Window {
    visible: true
    width: 640
    height: 480

    ColorGradient {
        id: layerGradient
        ColorGradientStop { position: 0.0; color: "black" }
        ColorGradientStop { position: 0.31; color: "tan" }
        ColorGradientStop { position: 0.32; color: "green" }
        ColorGradientStop { position: 0.40; color: "darkslategray" }
        ColorGradientStop { position: 1.0; color: "white" }
    }

    Surface3D {
        width: parent.width
        height: parent.height
        theme: Theme3D {
            type: Theme3D.ThemeEbony
            font.pointSize: 35
            colorStyle: Theme3D.ColorStyleRangeGradient
        }
        shadowQuality: AbstractGraph3D.ShadowQualityNone
        selectionMode: AbstractGraph3D.SelectionRow | AbstractGraph3D.SelectionSlice
        scene {
            activeCamera.cameraPreset: Camera3D.CameraPresetIsometricLeft
        }
        axisY {
            min: 20; max: 200; segmentCount: 5;
            subSegmentCount: 2; labelFormat: "%i"
        }
        axisX { segmentCount: 5; subSegmentCount: 2; labelFormat: "%i" }
        axisZ { segmentCount: 5; subSegmentCount: 2; labelFormat: "%i" }

        Surface3DSeries {
            baseGradient: layerGradient
            drawMode: Surface3DSeries.DrawSurface
            flatShadingEnabled: false
            HeightMapSurfaceDataProxy {
                heightMapFile: "./layer.png"
            }
        }
    }
}
