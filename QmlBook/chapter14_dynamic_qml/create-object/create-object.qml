import QtQuick 2.12

Item {
    id: root
    width: 1024
    height: 640

    function createItem() {
        Qt.createQmlObject("import QtQuick 2.12; Rectangle { x: 100; y: 100;" +
            "width: 100; height: 100; color: 'blue'}", root, "dynamicItem");
    }

    Component.onCompleted: root.createItem()
}
