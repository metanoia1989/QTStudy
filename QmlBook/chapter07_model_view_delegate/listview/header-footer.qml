import QtQuick 2.12
import "../common"

Background {
    width: 240
    height: 300

    ListView {
        anchors.fill: parent
        anchors.margins: 20
        currentIndex: 0
        clip: true
        model: 4
        delegate: numberDelegate
        spacing: 4
        header: headerComponent
        footer: footerComponent
    }

    Component {
        id: numberDelegate

        GreenBox {
            width: ListView.view.width
            height: 40
            text: "Item #" + index
        }
    }

    Component {
        id: headerComponent

        YellowBox {
            width: ListView.view.width
            height: 20
            text: "Header"
        }
    }

    Component {
        id: footerComponent

        YellowBox {
            width: ListView.view.width
            height: 20
            text: "Footer"
        }
    }
}
