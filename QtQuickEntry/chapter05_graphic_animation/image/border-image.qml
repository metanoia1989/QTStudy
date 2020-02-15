import QtQuick 2.12

Item {
    width: 400; height: 200

    BorderImage {
        source: "colors.png"
        width: 180; height: 180
        border { left: 30; top: 30; right: 30; bottom: 30 }
        horizontalTileMode: BorderImage.Stretch
        verticalTileMode: BorderImage.Stretch
    }

    BorderImage {
        x: 200
        source: "colors.png"
        width: 180; height: 180
        border { left: 30; top: 30; right: 30; bottom: 30 }
        horizontalTileMode: BorderImage.Repeat
        verticalTileMode: BorderImage.Repeat
    }
}

