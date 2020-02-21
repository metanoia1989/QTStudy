import QtQuick 2.12

Loader {
    id: root
    source: "http://127.0.0.1:9000/main2.qml"
    onLoaded: {
        root.width = item.width;
        root.height = item.height;
    }
}
