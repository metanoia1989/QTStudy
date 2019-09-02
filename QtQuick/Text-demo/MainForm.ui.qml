import QtQuick 2.4


Rectangle {
    Text {	// 普通纯文本
        x: 60
        y: 100
        color: "green"
        font.family: "Helvetica"
        font.pointSize: 24
        text: "Hello Qt Quick"
    }

    Text {	// 富文本
        x: 60
        y: 140
        color: "green"
        font.family: "Helvetica"
        font.pointSize: 24
        text: "<b>Hello</b> <i>Qt Quick!</i>"
    }

    Text {	// 带样式的文本
        x: 60
        y: 180
        color: "green"
        font.family: "Helvetica"
        font.pointSize: 24
        text: "Hello Qt Quick!"
        style: Text.Qutline; styleColor: "blue"
    }

    Text {	// 文本截断
        width: 200
        color: "green"
        font.family: "Helvetica"
        font.pointSize: 24
        horizontalAlignment: Text.AlignLeft // 左对齐
        verticalAlignment: Text.AlignTop
        elide: Text.ElideRight
        text: "Hello Qt Quick!"
    }

    Text {	// 换行的文本
        width: 200
        y: 30
        color: "green"
        font.family: "Helvetica"
        font.pointSize: 24
        horizontalAlignment: Text.AlignLeft // 左对齐
        wrapMode: Text.WrapAnywhere
        text: "Hello Qt Quick!"
    }
}
