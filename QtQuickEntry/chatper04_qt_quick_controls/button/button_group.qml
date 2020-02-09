import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 250; height:200

    Column {
        spacing: 20
        anchors.centerIn: parent

        ButtonGroup { buttons: row.children }
        Row {
            id: row
            RadioButton { checked: true; text: qsTr("DAB") }
            RadioButton { text: qsTr("FM") }
            RadioButton { text: qsTr("AM") }
        }

        ButtonGroup { id: radioGroup }
        Row {
            RadioButton { checked: true; text: qsTr("DAB"); ButtonGroup.group: radioGroup }
            RadioButton { text: qsTr("FM"); ButtonGroup.group: radioGroup }
            RadioButton { text: qsTr("AM"); ButtonGroup.group: radioGroup }
        }
    }
}
