import QtQuick 2.0

Item {
    property color defaultColor: "blue"
    ListView {
        delegate: Component {
            Rectangle { color: defaultColor }
        }
    }
}
