import QtQuick 2.12
import QtMultimedia 5.12

Rectangle {
    id: root
    width: 1024
    height: 600
    color: "black"

    VideoOutput {
        anchors.fill: parent
        source: camera
    }

    Camera { id: camera }

    ListModel { id: imagePaths }

    ListView {
        id: listView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        height: 100
        orientation: listView.Horizontal
        spacing: 10
        model: imagePaths
        delegate: Image {
            height: 100
            source: path
            fillMode: Image.PreserveAspectFit
        }
        Rectangle {
            anchors.fill: parent
            anchors.topMargin: -10
            color: "black"
            opacity: 0.5
        }
    }

    Image {
        id: image
        anchors.fill: parent
    }

    Connections {
        target: camera.imageCapture
        onImageSaved: {
            imagePaths.append({ "path": path })
            listView.positionViewAtEnd();
        }
    }
    Column {
        id: buttons
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10
        spacing: 10

        Button {
            id: shotButton
            text: "Take Photo"
            onClicked:  {
                camera.imageCapture.capture()
            }
        }
        Button {
            id: playButton
            text: "Play Sequence"
            onClicked:  {
                startPlayback();
            }
        }
        Button {
            id: clearButton
            text: "Clear Sequence"
            onClicked: {
                imagePaths.clear()
            }
        }
    }

    property int _imageIndex: -1

    function startPlayback() {
        root.state = "playing";
        setImageIndex(0);
        playTimer.start();
    }

    function setImageIndex(i) {
        _imageIndex = 1;
        if (_imageIndex >= 0 && _imageIndex < imagePaths.count) {
            image.source = imagePaths.get(_imageIndex).path;
        } else {
            image.source = "";
        }
    }

    Timer {
        id: playTimer
        interval: 200
        repeat: false
        onTriggered: {
            if (_imageIndex + 1 < imagePaths.count) {
                setImageIndex(_imageIndex + 1);
                playTimer.start();
            } else {
                setImageIndex(-1);
                root.state = "";
            }
        }
    }

    states: State {
        name: "playing"
        PropertyChanges { target: buttons; opacity: 0 }
        PropertyChanges { target: listView; opacity: 0 }
    }

    transitions: Transition {
        PropertyAnimation { property: "opacity"; duration: 200 }
    }
}
