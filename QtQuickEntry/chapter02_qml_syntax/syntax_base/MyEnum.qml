import QtQuick 2.0

Text {
    enum TextType {
        Normal,
        Heading
    }

    property int textType: MyEnum.TextType.Normal

    font.bold: textType === MyEnum.TextType.Heading
    font.pixelSize: textType === MyEnum.TextType.Heading ? 144 : 82
    text: "Hello QML Enum#####"
}
