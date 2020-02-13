import QtQuick 2.12
import QtQuick.Window 2.2
import QtDataVisualization 1.3

Window {
    visible: true
    width: 640
    height: 480

    Surface3D {
        width: parent.width
        height: parent.height
        flipHorizontalGrid: true

        Surface3DSeries {
            itemLabelFormat: "Pop density at (@xLabel N, @zLabel E): @yLabel"
            ItemModelSurfaceDataProxy {
                itemModel: dataModel
                rowRole: "longitude"
                columnRole: "latitude"
                yPosRole: "pop_density"
            }
        }
    }

    ListModel {
        id: dataModel
        ListElement { longitude: "20"; latitude: "10"; pop_density: "4.75" }
        ListElement { longitude: "21"; latitude: "10"; pop_density: "3.00" }

        ListElement { longitude: "20"; latitude: "11"; pop_density: "2.55" }
        ListElement { longitude: "21"; latitude: "11"; pop_density: "2.03" }

        ListElement { longitude: "20"; latitude: "12"; pop_density: "1.37" }
        ListElement { longitude: "21"; latitude: "12"; pop_density: "2.98" }

        ListElement { longitude: "20"; latitude: "13"; pop_density: "4.34" }
        ListElement { longitude: "21"; latitude: "13"; pop_density: "3.54" }
    }
}
