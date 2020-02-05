import QtQuick 2.0

Rectangle {
    id: photo	// id 声明
    property bool thumbnail: false	// 属性声明
    property alias image: photoImage.source
    signal clicked	// 信号声明

    function doSomething(x) {	// javascript 函数
        return x + photoImage.width
    }

    color: "gray"	// 对象属性
    x: 20; y: 20; height: 20 // 相关属性放在一起
    width: {	// 属性绑定
        if (photoImage.width > 200) {
            photoImage.width;
        } else {
            200;
        }
    }

    Rectangle {	// 子对象
        id: border
        anchors.centerIn: parent; color: "white"
        Image {
            id: photoImage;
            anchors.centerIn: parent
        }
    }

    states: State {	// 状态
        name: "selected"
        PropertyChanges {
            target: border
            color: "red"
        }
    }

    transitions: Transition {	// 过渡 状态切换
        from: ""
        to: "selected"
        ColorAnimation {
            target: border
            duration: 200
        }
    }
}
