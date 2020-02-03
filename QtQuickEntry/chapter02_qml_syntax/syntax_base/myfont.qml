import QtQuick 2.0

Text {
    onFontChanged: console.log("font change")
    text: "Hello Qt!"
    Text {
        id: otherText
    }
    focus: true
    // 下面的操作都会调用 onFontChanged 信号处理器
    Keys.onDigit1Pressed: font.pixelSize += 1
    Keys.onDigit2Pressed: font.italic != font.italic
    Keys.onDigit3Pressed: font = otherText.font
}
