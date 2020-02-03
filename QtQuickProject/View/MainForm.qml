import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3

Item {
    width: 780
    height: 320

    property alias tableView: tableView	// TableView 视图
    property alias tabView: tabView	// TabView 视图
    property alias scrolimg: scrolimg // ScrollView 视图的Image子元素

    RowLayout {
        anchors.centerIn: parent
        SplitView {
            anchors.fill: parent
            orientation: Qt.Horizontal
            TableView {	/* TableView 视图 */
                id: tableView
                width: 300
                TableViewColumn {
                    role: "title"
                    title: "名称"
                    horizontalAlignment: Text.AlignHCenter
                    width: 100
                }
                TableViewColumn {
                    role: "author"
                    title: "作者"
                    horizontalAlignment: Text.AlignHCenter
                    width: 200
                }
                model: libraryModel	// 指定负责提供数据的 ListModel 对象
            }
            TabView { /* TabView 视图 */
                id: tabView
                width: 215; height: 300
                Tab {
                    title: "mnls"
                    Image {
                        source: "images/mnls.jpg"
                    }
                }
                Tab {
                    title: "dw"
                    Image {
                        source: "images/dw.jpg"
                    }
                }
                Tab {
                    title: "sm"
                    Image {
                        source: "images/sm.jpg"
                    }
                }
            }
            ScrollView {
                Image {
                    id: scrolimg
                    source: "images/mnls.jpg"
                }
            }
        }
    }
    ListModel {	// 提供TableView视图所需数据
        id: libraryModel
        ListElement {
            title: "蒙娜丽莎"
            author: "列奥纳多~达~芬奇"
        }
        ListElement {
            title: "大卫"
            author: "博纳罗蒂~米开朗基罗"
        }
        ListElement {
            title: "西斯廷圣母"
            author: "拉斐尔~圣奇奥"
        }
    }
}
