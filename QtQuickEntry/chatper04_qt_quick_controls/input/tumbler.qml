import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 250; height: 200

    Row {
        Tumbler { id: hoursTumbler; model: 12 }
        Tumbler { id: minutesTumbler; model: 60 }
        Tumbler { id: amPmTumbler; model: ["AM", "PM"] }
    }
}
