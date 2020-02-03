import QtQuick 2.0

Rectangle {
    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }

    Row { 	// 将所有图标成一行横向排列
        x: 50; y: 50
        spacing: 30
        Rectangle { 	// 第一个矩形元素 音乐图标
            id: music
            width: 100; height: 100
            radius: 6
            color: focus ? "red" : "lightgray" // 获得焦点为红
            scale: focus ? 1 : 0.8 // 获得焦点时变大
            focus: true
            KeyNavigation.tab: play
            /* 移动图标位置 */
            Keys.onUpPressed: music.y -= 10 	// 上移
            Keys.onDownPressed: music.y += 10 	// 下移
            Keys.onLeftPressed: music.x -= 10 	// 左移
            Keys.onRightPressed: music.x += 10 	// 右移
            Text {	// 图标上显示的文本
                anchors.centerIn: parent
                color: parent.focus ? "black" : "gray"
                font.pointSize: 20
                text: "音乐"
            }
        }
        Rectangle { 	// 第二个矩形元素 游戏图标
            id: play
            width: 100; height: 100
            radius: 6
            color: focus ? "green" : "lightgray" // 获得焦点为红
            scale: focus ? 1 : 0.8 // 获得焦点时变大
            KeyNavigation.tab: movie
            /* 移动图标位置 */
            Keys.onUpPressed: play.y -= 10 	// 上移
            Keys.onDownPressed: play.y += 10 	// 下移
            Keys.onLeftPressed: play.x -= 10 	// 左移
            Keys.onRightPressed: play.x += 10 	// 右移
            Text {	// 图标上显示的文本
                anchors.centerIn: parent
                color: parent.focus ? "black" : "gray"
                font.pointSize: 20
                text: "游戏"
            }
        }
        Rectangle { 	// 第三个矩形元素 电影图标
            id: movie
            width: 100; height: 100
            radius: 6
            color: focus ? "blue" : "lightgray" // 获得焦点为红
            scale: focus ? 1 : 0.8 // 获得焦点时变大
            KeyNavigation.tab: music
            /* 移动图标位置 */
            Keys.onUpPressed: movie.y -= 10 	// 上移
            Keys.onDownPressed: movie.y += 10 	// 下移
            Keys.onLeftPressed: movie.x -= 10 	// 左移
            Keys.onRightPressed: movie.x += 10 	// 右移
            Text {	// 图标上显示的文本
                anchors.centerIn: parent
                color: parent.focus ? "black" : "gray"
                font.pointSize: 20
                text: "影视"
            }
        }
    }
}
