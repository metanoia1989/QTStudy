import QtQuick 2.12
import QtQuick.XmlListModel 2.12

Rectangle {
    width: 500; height: 340

    XmlListModel {
        id: xmlModel
        source: "http://www.people.com.cn/rss/edu.xml"
        query: "/rss/channel/item"
        XmlRole { name: "title"; query: "title/string()" }
        XmlRole { name: "pubDate"; query: "pubDate/string()" }
    }

    ListView {
        width: 180; height: 300
        model: xmlModel
        delegate: Text { text: title + ": " + pubDate }
        spacing: 5
    }
}
