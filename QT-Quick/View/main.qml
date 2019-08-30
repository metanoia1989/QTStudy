import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 780
    height: 320
    title: qsTr("世界艺术珍品")
    MainForm {
        anchors.fill: parent
        tableView.onClicked: {	// 单击列表项执行的代码
            tabView.currentIndex = tableView.currentRow;
            scrolimg.source = "images/" + tabView.getTab(tabView.currentIndex).title + ".jpg";
        }
        tabView.onCurrentIndexChanged: {	// 切换TabView视图选项卡执行的代码
            tableView.selection.clear();
            tableView.selection.select(tabView.currentIndex);
            scrolimg.source = "images/" + tabView.getTab(tabView.currentIndex).title + ".jpg";
        }
    }
}
