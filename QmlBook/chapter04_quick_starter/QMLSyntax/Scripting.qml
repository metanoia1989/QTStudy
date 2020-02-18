import QtQuick 2.12


Item {
    width: 100; height: 100

    Text {
        id: label
        x: 24; y: 24
        property int spacePresses: 0
        text: "Space pressed: " + spacePresses + " times"
        onTextChanged: console.log("textchanged to: ", text)
        focus: true // 聚焦，接收键盘事件
        Keys.onSpacePressed: {
            increment(); // 调用JS
        }
        Keys.onEscapePressed: {
            label.text = "";
        }
        function increment() {
            spacePresses = spacePresses + 1;
        }
    }
}
