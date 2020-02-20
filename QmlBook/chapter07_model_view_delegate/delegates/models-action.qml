import QtQuick 2.12

Rectangle {
    width: 120
    height: 300
    gradient: Gradient {
        GradientStop { position: 0.0; color: "#f6f6f6" }
        GradientStop { position: 1.0; color: "#d7d7d7" }
    }

    ListView {
        anchors.fill: parent
        anchors.margins: 20
        clip: true
        model: actionModel
        delegate: actionDelegate
        spacing: 5
        focus: true
    }

    ListModel {
        id: actionModel

        ListElement {
            name: "Copehagen"
            hello: (value) => console.log(value + ": You clicked Copenhagen!");
        }
        ListElement {
            name: "Helsinki"
            hello: (value) => console.log(value + ": You Helsinki here!");
        }
        ListElement {
            name: "Oslo"
            hello: (value) => console.log(value + ": Hei Hei fra Oslo!");
        }
        ListElement {
            name: "Stockholm"
            hello: (value) => console.log(value + ": Stockholm calling!");
        }
    }

    Component {
        id: actionDelegate

        Rectangle {
            width: ListView.view.width
            height: 40
            color: "#157efb"

            Text {
                anchors.centerIn: parent
                font.pixelSize: 10
                text: name
            }

            MouseArea {
                anchors.fill: parent
                onClicked: hello(index)
            }
        }
    }
}
