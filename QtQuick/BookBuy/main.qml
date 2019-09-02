import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("选购图书")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {
            Label {
                text: qsTr("Second Page")
                anchors.centerIn: parent
            }
        }

        Page {
            ListView {
                id: listView
                anchors.fill: parent
                model: bookModel
                delegate: SwipeDelegate {
                    id: swipeDelegate
                    text: model.title + " - " + model.sender
                    width: parent.width
                    font.family: "楷体"
                    font.bold: true
                    font.pointSize: 12

                    onClicked: listView.currentIndex = index

                    ListView.onRemove: SequentialAnimation {
                        PropertyAction {
                            target: swipeDelegate
                            property: "ListView.delayRemove"
                            value: true
                        }
                        NumberAnimation {
                            target: swipeDelegate
                            property: "height"
                            to: 0
                            easing.type: Easing.InOutQuad
                        }
                        PropertyAction {
                            target: swipeDelegate
                            property: "ListView.delayRemove"
                            value: false
                        }
                    }

                    swipe.right: Row {
                        anchors.right: parent.right
                        height: parent.height
                        Label {
                            id: moveLabel
                            text: qsTr("购买")
                            color: "black"
                            font.family: "黑体"
                            font.pointSize: 12
                            verticalAlignment: Label.AlignVCenter
                            padding: 12
                            height: parent.height
                            SwipeDelegate.onClicked: {
                                switch (index) {
                                    case 0: bookCover.source="images/java.jpg"; break;
                                    case 1: bookCover.source="images/javaee.jpg"; break;
                                    case 2: bookCover.source="images/mysql.jpg"; break;
                                    case 3: bookCover.source="images/orcl.jpg"; break;
                                    case 4: bookCover.source="images/php.jpg"; break;
                                    case 5: bookCover.source="images/plc.jpg"; break;
                                    case 6: bookCover.source="images/sqlsrv.jpg"; break;
                                    default: break;
                                }
                            }
                            background: Rectangle {
                                color: moveLabel.SwipeDelegate.pressed ? Qt.darker("#ffbf47", 1.1) : "#ffbf47"
                            }
                        }
                        Label {
                            id: deleteLabel
                            text: qsTr("移除")
                            color: "black"
                            font.family: "黑体"
                            font.pointSize: 12
                            verticalAlignment: Label.AlignVCenter
                            padding: 12
                            height: parent.height
                            SwipeDelegate.onClicked: listView.model.remove(index)
                            background: Rectangle {
                                color: deleteLabel.SwipeDelegate.pressed ? Qt.darker("tomato", 1.1) : "tomato"
                            }
                        }
                    }
                }
            }

            RowLayout {
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                Image {
                    id: bookCover
                    source: "images/java.jpg"
                }
                Button {
                    text: "结账"
                    font.family: "楷体"
                    font.bold: true
                    font.pointSize: 14
                    ToolTip.visible: down
                    ToolTip.text: qsTr("可选择付款方式")
                    onClicked: popup.open()	// 单击弹出组框
                }
                Popup {
                    id: popup
                    ColumnLayout {
                        anchors.fill: parent
                        Label {
                            text: qsTr("请选择付款方式：")
                        }
                        CheckBox { text: qsTr("手机支付宝") }
                        CheckBox { text: qsTr("微信红包") }
                        CheckBox { text: qsTr("网银快捷支付") }
                    }
                    enter: Transition {
                        NumberAnimation {
                            property: "opacity"
                            from: 0.0
                            to: 0.8
                        }
                    }
                    exit: Transition {
                        NumberAnimation {
                            property: "opacity"
                            from: 0.8
                            to: 0.0
                        }
                    }
                }
            }
            ListModel {
                id: bookModel
                ListElement { title: "《Java实用教程(第3版)》"; sender: "ISBN：9787121266225  单价:￥52.00" }
                ListElement { title: "《JavaEE基础实用教程(第2版)》"; sender: "ISBN：9787121252068  单价:￥49.00" }
                ListElement { title: "《MySQL实用教程(第2版)》"; sender: "ISBN：9787121232701  单价:￥53.00" }
                ListElement { title: "《Oracle实用教程(第4版)》"; sender: "ISBN：9787121273803  单价:￥49.00" }
                ListElement { title: "《PHP实用教程(第2版)》"; sender: "ISBN：9787121243394  单价:￥45.00" }
                ListElement { title: "《施耐德PLC开发及实例(第2版)》"; sender: "ISBN：9787121259821  单价:￥59.00" }
                ListElement { title: "《SQLServer实用教程(第4版)》"; sender: "ISBN：9787121266232  单价:￥49.00" }
            }
        }

    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("First")
        }
        TabButton {
            text: qsTr("Second")
        }
    }
}
