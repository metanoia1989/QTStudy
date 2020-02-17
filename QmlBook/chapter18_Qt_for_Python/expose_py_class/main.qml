import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import Generators 1.0

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: "Hello Python World!"

    Flow {
        Button {
            text: "Give me o number!"
            onClicked: numberGenerator.giveNumber();
        }
        Label {
            id: numberLabel
            text: "no number"
        }
    }

    NumberGenerator {
        id: numberGenerator
        // 信号参数名不会从Python传播到QML，因此我们需要重新发出信号
        signal reNextNumber(int number)
        Component.onCompleted: numberGenerator.nextNumber.connect(reNextNumber)
    }

    Connections {
        target: numberGenerator
        onReNextNumber: numberLabel.text = number
    } 
}