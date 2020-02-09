import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 250; height:200

    Column {
        spacing: 20
        anchors.centerIn: parent

        Row {
            CheckBox {
                id: allChildrenChecked
                text: qsTr("All Checked")
            }
            CheckBox {
                id: partlyChildrenChecked
                text: qsTr("Partly Checked")
            }
        }
        CheckBox {
            text: qsTr("Result")
            tristate: true
            checkState: allChildrenChecked.checked ? Qt.Checked :
                        partlyChildrenChecked.checked ? Qt.PartiallyChecked : Qt.Unchecked
            nextCheckState: () => {
                return checkState === Qt ? Qt.Unchecked : Qt.Checked;
            }

        }
    }
}
