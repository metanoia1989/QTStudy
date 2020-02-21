import QtQuick 2.12

Loader {
    source: 'http://localhost:9000/main.qml#' + new Date().getTime()
}
