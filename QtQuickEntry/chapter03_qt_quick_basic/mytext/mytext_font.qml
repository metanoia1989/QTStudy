import QtQuick 2.2

Column {
    FontLoader {
        id: fixedFont
        name: "Courier"
    }
    FontLoader {
        id: webFont
        source: "http://www.mysize.com/myfont.ttf"
    }
    Text {
        text: "Fixed - size font"
        font.family: fixedFont.name
    }
    Text {
        text: "Fancy font"
        font.family: webFont.name
    }
}