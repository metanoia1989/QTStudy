import QtQuick 2.12
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4	// Qt Quick 控件样式库

ApplicationWindow {
    visible: true
    width: 600
    height: 240
    title: qsTr("样式定制")
    MainForm {
        anchors.fill: parent
    }
}
