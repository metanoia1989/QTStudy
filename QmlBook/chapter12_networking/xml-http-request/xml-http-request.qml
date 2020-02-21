import QtQuick 2.14

Rectangle {
    width: 320
    height: 480

    ListView {
        id: view
        anchors.fill: parent
        delegate: Thumbnail {
            width: view.width
            text: modelData.title
            iconSource: modelData.media.m
        }
    }

    function request() {
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.HEADERS_RECEIVED) {
                print("HEADERS_RECEIVED");
            } else if (xhr.readyState === XMLHttpRequest.DONE) {
                print("DONE")
                var json = JSON.parse(xhr.responseText.toString());
                view.model = json.items;
            }
        }
        xhr.open("GET", "http://localhost:9000/photo.json");
        xhr.send();
    }

    Component.onCompleted: {
        request();
    }
}
