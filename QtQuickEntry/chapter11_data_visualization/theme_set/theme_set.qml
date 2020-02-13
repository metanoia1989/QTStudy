import QtQuick 2.9
import QtQuick.Window 2.2
import QtDataVisualization 1.2

Window {
    visible: true
    width: 640
    height: 480

    ThemeColor {
        id: dynamicColor
        color: "gold"
    }
    ThemeColor {
        id: dynamicColor2
        color: "lightgreen"
    }
    Theme3D {
        id: userDefinedTheme
        ambientLightStrength: 0.5
        backgroundColor: "transparent"
        backgroundEnabled: true
        baseColors: [dynamicColor, dynamicColor2]
        colorStyle: Theme3D.ColorStyleUniform
        font.pointSize: 35
        font.bold: true
        gridLineColor: "grey"
        highlightLightStrength: 0.5
        labelBackgroundColor: "transparent"
        labelBorderEnabled: false
        labelTextColor: "white"
        lightColor: "white"
        lightStrength: 7.0
        singleHighlightColor: "lightblue"
        windowColor: "black"
    }
    Bars3D {
        width: parent.width
        height: parent.height
        scene {
            activeCamera.cameraPreset: Camera3D.CameraPresetIsometricRightHigh
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
