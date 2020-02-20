import QtQuick 2.12
import QtQuick.XmlListModel 2.12
import "../common"

Background {
    width: 300
    height: 480

    ListView {
        id: listView
        anchors.fill: parent
        model: imageModel
        delegate: imageDelegate
    }

    XmlListModel {
        id: imageModel

        source: "https://www.nasa.gov/rss/dyn/image_of_the_day.rss"
        query: "/rss/channel/item"

        XmlRole { name: "title"; query: "title/string()" }
        XmlRole { name: "imageSource"; query: "enclosure/string(@url)" }
    }

    Component {
        id: imageDelegate

        Box {
            width: listView.width
            height: 220
            color: "#333"

            Column {
                Text { text: title; color: "#e0e0e0" }
                Image {
                    width: listView.width
                    height: 200
                    fillMode: Image.PreserveAspectCrop
                    source: imageSource
                }
            }
        }
    }
}
