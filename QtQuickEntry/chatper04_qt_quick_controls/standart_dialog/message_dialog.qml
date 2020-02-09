import QtQuick 2.12
import QtQuick.Controls 2.12

import QtQuick.Dialogs 1.3

ApplicationWindow {
    id: widnow
    visible: true
    width: 300; height: 300
    Button {
        width: 150; height: 50; text: "Message Dialog"
        anchors.centerIn: parent
        onClicked: messageDialog.open()
    }
    MessageDialog {
        id: messageDialog
        title: "May I have your attention please"
        text: "It's so cool that your are using Qt Quick."
        detailedText: "this is the detailed text!"
        icon: StandardIcon.Question
        standardButtons: StandardButton.Yes | StandardButton.Help
                        | StandardButton.Open
        onYes:  console.log("yes.")
        onHelp:  console.log("help.")
        onAccepted:  console.log("open.")
    }
}
