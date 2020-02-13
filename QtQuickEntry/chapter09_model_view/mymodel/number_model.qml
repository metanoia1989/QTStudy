import QtQuick 2.12

Item {
    width: 200; height: 100

    Component {
        id: myDelegate
        Text { text: "I am item number: " + index; font.pointSize: 12 }
    }

    ListView {
        anchors.fill: parent
        model: 5; delegate: myDelegate
    }
}
