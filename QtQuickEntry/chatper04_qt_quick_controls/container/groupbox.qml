import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ApplicationWindow {
    visible: true
    width: 400; height: 400
    title: qsTr("GroupBox")

    GroupBox {
        label: CheckBox { id: checkBox; checked: true; text: qsTr("Synchronize") }
        ColumnLayout {
            anchors.fill: parent
            enabled: checkBox.checked
            CheckBox { text: qsTr("E-mail") }
            CheckBox { text: qsTr("Calendar") }
            CheckBox { text: qsTr("Contacts") }
        }
    }
}
