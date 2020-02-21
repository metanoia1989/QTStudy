import QtQuick 2.12

ListView {
    id: root
    width: 100
    height: 62
    model: ListModel { }
    delegate: Row {
        width: root.width
        height: 18
        property real cw: width / 24
        Label {
            width: cw * 1
            height: parent.height
            text: model.prefix
        }
        Label {
            width: cw * 23
            height: parent.height
            text: model.message
        }
    }
    function append(prefix, message) {
        model.append({ prefix: prefix, message: message });
    }
}

