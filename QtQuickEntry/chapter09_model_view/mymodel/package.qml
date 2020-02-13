import QtQuick 2.9
import QtQml.Models 2.12

Rectangle {
    width: 200; height: 300

    DelegateModel {
        id: delegateModel
        delegate: Package {
            Text {
                id: listDelegate;
                width: parent.width;
                height: 25;
                text: "in list";
                Package.name: "list"
            }
            Text {
                id: gridDelegate;
                width: parent.width / 2;
                height: 50;
                text: "in grid";
                Package.name: "grid"
            }
        }
        model: 5
    }

    Rectangle {
        height: parent.height / 2; width: parent.width
        color: "lightgrey"
        ListView {
            anchors.fill: parent
            model: delegateModel.parts.list
        }
    }

    GridView {
        y: parent.height / 2;
        height: parent.height / 2; width: parent.width;
        cellWidth: width / 2; cellHeight: 50
        model: delegateModel.parts.grid
    }
}
