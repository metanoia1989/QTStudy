import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 250; height: 200

    ComboBox {
        width: 200; currentIndex: 2
        textRole: "text"; editable: true
        model: ListModel {
            id: cbItems
            ListElement { text: "Banana"; color: "Yellow" }
            ListElement { text: "Apple"; color: "Green" }
            ListElement { text: "Cocount"; color: "Brown" }
        }
        onAccepted: {
            if (find(editText) === -1) {
                model.append({text: editText})
            }
        }
    }
}
